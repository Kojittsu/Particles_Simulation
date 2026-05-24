#include "renderer.h"

Renderer::Renderer()
{
    quadric_ = gluNewQuadric();
    Camera camera_;
    initializeGLFW();
    initializeImGui();
    initializeImPlot();
}

Renderer::~Renderer() {

    ImPlot::DestroyContext();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window_);
    glfwTerminate();

    if (quadric_) {
        gluDeleteQuadric(quadric_);
    }
}

void Renderer::initializeGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    window_ = glfwCreateWindow(900, 600, "Particle System", NULL, NULL);
    if (!window_) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW Window.");
    }

    glfwMakeContextCurrent(window_);

    // Associate actual instance to the window
    glfwSetWindowUserPointer(window_, this);

    // Set framebuffer size callback
    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* win, int width, int height) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->framebufferSizeCallback(width, height);
        }
    });

    // Set cursor callback
    glfwSetCursorPosCallback(window_, [](GLFWwindow* win, double xpos, double ypos) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->cursorPosCallback(xpos, ypos);
        }
    });

    // Set key callback
    glfwSetKeyCallback(window_, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->keyboardCallback(key, scancode, action, mods);
        }
    });

    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetTime(0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void Renderer::framebufferSizeCallback(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);

    camera_.configurePerspective(aspectRatio);

    glMatrixMode(GL_MODELVIEW);
}

void Renderer::cursorPosCallback(double xpos, double ypos) {
    if(isSpectatorMode_) {
        float xOffset = xpos - lastX_;
        float yOffset = lastY_ - ypos; // Reverse the Y offset so that the upward movement is positive
        camera_.computeNewOrientation(xOffset, yOffset);
    }

    lastX_ = xpos;
    lastY_ = ypos;
}

void Renderer::keyboardCallback(int key, int scancode, int action, int mods) {
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keyStates_[key] = true;
        } else if (action == GLFW_RELEASE) {
            keyStates_[key] = false;
        }
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && isSpectatorMode_) {
        toggleSpectatorMode();
    }
}

void Renderer::initializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    // ImGui/Glfw bindings
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Renderer::initializeImPlot() {
    ImPlot::CreateContext();

    lastFrameratesBuffer_ = std::vector<float>(100, 0.0f);

    lastFrameratesIndexes_ = std::vector<float>(lastFrameratesBuffer_.size());
    for (std::size_t i = 0; i < lastFrameratesIndexes_.size(); ++i) {
        lastFrameratesIndexes_[i] = static_cast<float>(i);
    }
}

void Renderer::setLoadConfigCallback(std::function<void()> cb) {
    loadConfigCallback_ = cb;
}

void Renderer::setUnloadConfigCallback(std::function<void()> cb) {
    unloadConfigCallback_ = cb;
}

void Renderer::setUniversePtr(Universe* universePtr) {
    universePtr_ = universePtr;
}

void Renderer::resetCurrentUniverse() {
    setUniversePtr(nullptr);
    // reset current universe variables
    currentUniverseRuntime_ = 0.0;
    currentUniverseTimePaused_ = 0.0;

    //  reset other renderer variables
    speedFactor_ = 1.0;
    scaleFactor_ = 1.0;
    camera_.reset();
}

void Renderer::updateConfig(const RendererConfig& rendererConfig) {
    speedFactor_ = rendererConfig.speedFactor;
    scaleFactor_ = rendererConfig.scaleFactor;
}

void Renderer::renderFrame() {
    clear();
    renderScene();
    renderImGui();

    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void Renderer::renderScene() {
    if(universePtr_) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrameTime_;

        lastFrameTime_ = currentFrame;

        // compute currentUniverseRuntime_ & currentUniverseTimePaused_
        if(universePtr_->isRunning_) {
            currentUniverseRuntime_ = currentFrame - currentUniverseTimePaused_;
        }
        else {
            currentUniverseTimePaused_ += deltaTime;
        }

        // Update camera
        if(isSpectatorMode_) {
            camera_.computeNewPosition(keyStates_, deltaTime);
        }

        camera_.update();

        auto& particles = universePtr_->getParticles();

        for (const auto& particle : particles) {
            renderParticle(particle);
        }

        if(renderParticleTrails_) {
            for (const auto& particle : particles) {
                renderParticleTrail(particle);
            }
        }

        renderBoxes();

        if(renderGrid_) {
            renderGrid();
        }
    }
}

void Renderer::renderParticle(const Particle& particle) {
    auto position = particle.getPosition() * scaleFactor_; // transform particle position from meter to SU
    auto color = particle.getColor();
    double radius = particle.getRadius() * scaleFactor_; // transform particle radius from meter to SU

    // Define material properties
    GLfloat mat_diffuse[] = { color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslated(position[0], position[1], position[2]);
    gluSphere(quadric_, radius, 16, 16);
    glPopMatrix();
}

void Renderer::renderParticleTrail(const Particle& particle) {
    const auto& trail = particle.getTrail();
    if (trail.size() < 2) { return; }

    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_STRIP);

    // set trail color
    auto color = particle.getColor();
    glColor3ub(color[0], color[1], color[2]);

    for (const auto& point : trail) {
        glVertex3d(point[0] * scaleFactor_, point[1] * scaleFactor_, point[2] * scaleFactor_);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void Renderer::renderBoxes() {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    for(Box& box : universePtr_->getBoxes()) {
        std::array<double, 3> boxOrigin = box.origin_  * scaleFactor_; // transform box from meter to SU

        float x0 = boxOrigin[0];
        float y0 = boxOrigin[1];
        float z0 = boxOrigin[2];

        float x1 = x0 + box.length_ * scaleFactor_; // transform box length from meter to SU
        float y1 = y0 + box.height_ * scaleFactor_; // transform box height from meter to SU
        float z1 = z0 + box.depth_ * scaleFactor_; // transform box depth from meter to SU

        glBegin(GL_LINES);
        glVertex3f(x0, y0, z0); glVertex3f(x1, y0, z0);
        glVertex3f(x1, y0, z0); glVertex3f(x1, y1, z0);
        glVertex3f(x1, y1, z0); glVertex3f(x0, y1, z0);
        glVertex3f(x0, y1, z0); glVertex3f(x0, y0, z0);

        glVertex3f(x0, y0, z1); glVertex3f(x1, y0, z1);
        glVertex3f(x1, y0, z1); glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z1); glVertex3f(x0, y1, z1);
        glVertex3f(x0, y1, z1); glVertex3f(x0, y0, z1);

        glVertex3f(x0, y0, z0); glVertex3f(x0, y0, z1);
        glVertex3f(x1, y0, z0); glVertex3f(x1, y0, z1);
        glVertex3f(x1, y1, z0); glVertex3f(x1, y1, z1);
        glVertex3f(x0, y1, z0); glVertex3f(x0, y1, z1);
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

void Renderer::renderGrid() {

    float gridHalfLength = gridLength_ / 2;

    glm::vec3 cameraPosition = camera_.getPosition();
    float offsetX = floor(cameraPosition.x / gridStep_) * gridStep_;
    float offsetZ = floor(cameraPosition.z / gridStep_) * gridStep_;

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, gridOpacity_);

    glBegin(GL_LINES);
    for (float i = -gridHalfLength; i <= gridHalfLength; i += gridStep_) {

        // // lines parallel to Z-axe
        glVertex3f(i + offsetX, 0.0f, -gridHalfLength + offsetZ);
        glVertex3f(i + offsetX, 0.0f,  gridHalfLength + offsetZ);

        // // lines parallel to X-axe
        glVertex3f(-gridHalfLength + offsetX, 0.0f, i + offsetZ);
        glVertex3f( gridHalfLength + offsetX, 0.0f, i + offsetZ);
    }
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void Renderer::renderImGui() {

    // Start new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Set dockspace
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), dockSpaceFlags_);

    ImGuiControlsMenu();

    ImGuiInformationMenu();

    ImGuiParticleViewerMenu();

    ImGuiParticleEditorMenu();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::ImGuiControlsMenu() {
    ImGui::Begin("Controls", nullptr, windowFlags_);
    // Set round corners
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

    if (ImGui::CollapsingHeader("Configuration loader")) {
        if (ImGui::Button("Load configuration") && loadConfigCallback_) {
            loadConfigCallback_();
        }

        if (ImGui::Button("Unload current configuration") && unloadConfigCallback_) {
            unloadConfigCallback_();
        }
    }

    if (universePtr_ && ImGui::CollapsingHeader("Simulation controls")) {
        if (ImGui::Button(universePtr_->isRunning_ ? "Pause simulation" : "Start simulation")) {
            universePtr_->isRunning_ = !universePtr_->isRunning_;
        }

        if (ImGui::Button("Toggle gravity")) {
            universePtr_->toggleGravity();
        }
        ImGui::SameLine();
        ImGui::Text(universePtr_->getIsGravity() ? "Gravity ON" : "Gravity OFF");
    }

    if (ImGui::CollapsingHeader("Rendering controls")) {
        bool isSpectatorMode = isSpectatorMode_;
        if (ImGui::Checkbox("Spectator mode", &isSpectatorMode)) {
            toggleSpectatorMode();
        }

        static bool showWireframe = false;
        if (ImGui::Checkbox("Wireframe mode", &showWireframe)) {
            glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);
        }

        ImGui::Checkbox("Render particle trails", &renderParticleTrails_);

        ImGui::Checkbox("Render grid", &renderGrid_);

        ImGui::PushItemWidth(100);
        static float cameraSpeedInSceneUnit = camera_.getSpeed();
        static float cameraSpeedInMeters = cameraSpeedInSceneUnit / scaleFactor_; // transform camera position from SU to meter
        if (ImGui::InputFloat("Set camera speed", &cameraSpeedInMeters, 0.0f, 0.0f, "%.3e m/s")) {
            cameraSpeedInSceneUnit = cameraSpeedInMeters * scaleFactor_; // transform camera position from meter to SU
            camera_.setSpeed(cameraSpeedInSceneUnit);
        }
        ImGui::PopItemWidth();

        ImGui::PushItemWidth(300);
        static glm::vec3 newCameraPositionInSceneUnit = camera_.getPosition();
        static glm::vec3 newCameraPositionInMeters = newCameraPositionInSceneUnit / static_cast<float>(scaleFactor_);  // transform camera position from SU to meter
        if(ImGui::InputFloat3("Set camera position", &newCameraPositionInMeters[0],"%.3e m")){
            newCameraPositionInSceneUnit = newCameraPositionInMeters * static_cast<float>(scaleFactor_);  // transform camera position from meter to SU
            camera_.setPosition(newCameraPositionInSceneUnit);
        }
        ImGui::PopItemWidth();
    }

    if (universePtr_ && ImGui::CollapsingHeader("Add particle")) {

        static std::array<double, 3> position     = {0.0, 0.0, 0.0};
        static std::array<double, 3> velocity     = {0.0, 0.0, 0.0};
        static std::array<double, 3> acceleration = {0.0, 0.0, 0.0};
        static double radius = 0.0;
        static double mass   = 0.0;
        static std::array<int, 3> color = {0, 0, 0};

        ImGui::Text("Position:");
        ImGui::InputDouble("X (m)", &position[0]);
        ImGui::InputDouble("Y (m)", &position[1]);
        ImGui::InputDouble("Z (m)", &position[2]);

        ImGui::Text("Velocity:");
        ImGui::InputDouble("Vx (m/s)", &velocity[0]);
        ImGui::InputDouble("Vy (m/s)", &velocity[1]);
        ImGui::InputDouble("Vz (m/s)", &velocity[2]);

        ImGui::Text("Radius:");
        ImGui::InputDouble("Radius (m)", &radius);

        ImGui::Text("Mass:");
        ImGui::InputDouble("Mass (Kg)", &mass);

        ImGui::Text("Color:");
        if (ImGui::Button("Random")) {
            color[0] = rand() % 256;
            color[1] = rand() % 256;
            color[2] = rand() % 256;
        }
        ImGui::SliderInt("R", &color[0], 0, 255);
        ImGui::SliderInt("G", &color[1], 0, 255);
        ImGui::SliderInt("B", &color[2], 0, 255);


        if (ImGui::Button("Confirm")) {
            try {
                Particle particle(position, velocity, acceleration, radius, mass, color);
                universePtr_->addParticle(particle);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid_argument exception occured when adding particle from GUI : " << e.what() << std::endl;
            }
        }
    }

    ImGui::PopStyleVar();

    ImGui::End();
}

void Renderer::ImGuiInformationMenu() {

    glm::vec3 cameraPosition = camera_.getPosition() / static_cast<float>(scaleFactor_); // transform camera position from SU to meter
    glm::vec3 cameraFront = camera_.getFront();
    glm::vec3 cameraUp = camera_.getUp();

    ImGui::Begin("Info", nullptr, windowFlags_);
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGui::Text("Window size : %.0f x %.0f", windowSize.x, windowSize.y);

    lastFrameratesBuffer_.erase(lastFrameratesBuffer_.begin());
    lastFrameratesBuffer_.push_back(ImGui::GetIO().Framerate);

    if (ImPlot::BeginPlot("Framerate per seconds", ImVec2(-1,150), ImPlotFlags_NoMouseText | ImPlotFlags_NoInputs)) {
        ImPlot::SetupAxis(ImAxis_X1, nullptr, ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_NoDecorations);
        ImPlot::SetupAxis(ImAxis_Y1, nullptr);
        ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 200);
        ImPlot::PlotLine("", lastFrameratesIndexes_.data(), lastFrameratesBuffer_.data(), lastFrameratesBuffer_.size());
        ImPlot::EndPlot();
    }

    if(universePtr_) {
        double universeSimulationTime = universePtr_->simuationTime_;
        int days    = static_cast<int>(universeSimulationTime / 86400);
        int hours   = static_cast<int>(static_cast<int>(universeSimulationTime) % 86400 / 3600);
        int minutes = static_cast<int>(static_cast<int>(universeSimulationTime) % 3600 / 60);
        int seconds = static_cast<int>(universeSimulationTime) % 60;
        ImGui::Text("Simulation time : %d days, %02d hours, %02d minutes, %02d seconds", days, hours, minutes, seconds);
        ImGui::Text("Simulation time : %.3f s", universeSimulationTime);
    }

    ImGui::Text("Current universe runtime (s) : %.3f", currentUniverseRuntime_);
    ImGui::Spacing();
    ImGui::Text("Camera position : (%.3e, %.3e, %.3e) m", cameraPosition.x, cameraPosition.y, cameraPosition.z);
    ImGui::Text("Camera front : (%.1f, %.1f, %.1f)", cameraFront.x, cameraFront.y, cameraFront.z);
    ImGui::Text("Camera up : (%.1f, %.1f, %.1f)", cameraUp.x, cameraUp.y, cameraUp.z);
    ImGui::Spacing();
    ImGui::Text("OpenGL version : %s", glGetString(GL_VERSION));
    ImGui::Text("ImGui version : %s", ImGui::GetVersion());
    ImGui::Text("ImPlot version : %s", IMPLOT_VERSION);
    ImGui::End();
}

void Renderer::ImGuiParticleViewerMenu() {
    if(universePtr_) {
        std::vector<Particle>& universeParticles = universePtr_->getParticles();

        ImGui::Begin("Particles viewer", nullptr, windowFlags_);
        ImGui::Text("Particle count : %ld", universeParticles.size());
        ImGui::Spacing();

        int particleIndex = 0;
        for (Particle& particle : universeParticles) {
            ImGui::Text("Name : %s", particle.getName().c_str());
            ImGui::Text("Position : (%.3e, %.3e, %.3e) m", particle.getX(), particle.getY(), particle.getZ());
            ImGui::Text("Velocity : (%.3e, %.3e, %.3e) m/s. %.3e m/s", particle.getVX(), particle.getVY(), particle.getVZ(), getMagnitude(particle.getVelocity()));
            ImGui::Text("Mass : %.3e Kg", particle.getMass());
            ImGui::Text("Radius : %.3e m", particle.getRadius());

            ImGui::Text("Color : ");
            ImGui::SameLine();
            std::string label = particle.getName().empty() ? "Unnamed##" + std::to_string(particleIndex) : particle.getName();
            std::array<int, 3> color = particle.getColor();
            ImVec4 imguiColor(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, 1.0f);
            ImGui::ColorButton(label.c_str(), imguiColor);

            ImGui::Spacing();
            particleIndex++;
        }
        ImGui::End();
    }
}

void Renderer::ImGuiParticleEditorMenu() {
    if(universePtr_) {
        std::vector<Particle>& universeParticles = universePtr_->getParticles();

        static int selectedIndex = 0;

        ImGui::Begin("Particle editor", nullptr, windowFlags_);
        ImGui::Columns(2, nullptr, true);

        // Left column (list particles)
        int particleIndex = 0;
        for (Particle& particle : universeParticles) {
            std::string label = particle.getName().empty() ? "Unnamed##" + std::to_string(particleIndex) : particle.getName();
            if (ImGui::Selectable(label.c_str(), selectedIndex == particleIndex)) {
                selectedIndex = particleIndex;
            }
            particleIndex++;
        }

        // Right column (edit selected particle)
        ImGui::NextColumn();
        Particle& selectedParticle = universeParticles[selectedIndex];
        ImGui::Text("%s", selectedParticle.getName().c_str());

        static std::array<double, 3> newPosition     = {0.0, 0.0, 0.0};
        ImGui::Text("Position : (%.3e, %.3e, %.3e) m", selectedParticle.getX(), selectedParticle.getY(), selectedParticle.getZ());
        ImGui::Text("New Position:"); ImGui::SameLine();
        ImGui::PushItemWidth(80);
        ImGui::InputDouble("##X", &newPosition[0], 0, 0, "%.3f"); ImGui::SameLine();
        ImGui::InputDouble("##Y", &newPosition[1], 0, 0, "%.3f"); ImGui::SameLine();
        ImGui::InputDouble("##Z", &newPosition[2], 0, 0, "%.3f"); ImGui::SameLine();
        ImGui::PopItemWidth();
        if(ImGui::Button("Confirm###PositionConfirmButton")) {
            selectedParticle.setPosition(newPosition);
            newPosition = {0.0, 0.0, 0.0};
        }

        ImGui::Spacing();

        static std::array<double, 3> newVelocity     = {0.0, 0.0, 0.0};
        ImGui::Text("Velocity : (%.3e, %.3e, %.3e) m", selectedParticle.getVX(), selectedParticle.getVY(), selectedParticle.getVZ());
        ImGui::Text("New Velocity:"); ImGui::SameLine();
        ImGui::PushItemWidth(80);
        ImGui::InputDouble("##VX", &newVelocity[0], 0, 0, "%.3f"); ImGui::SameLine();
        ImGui::InputDouble("##VY", &newVelocity[1], 0, 0, "%.3f"); ImGui::SameLine();
        ImGui::InputDouble("##VZ", &newVelocity[2], 0, 0, "%.3f"); ImGui::SameLine();
        ImGui::PopItemWidth();
        if(ImGui::Button("Confirm###VelocityConfirmButton")) {
            selectedParticle.setVelocity(newVelocity);
            newVelocity = {0.0, 0.0, 0.0};
        }
        ImGui::End();
    }
}

void Renderer::toggleSpectatorMode() {
    isSpectatorMode_ = !isSpectatorMode_;
    if (isSpectatorMode_) {
       glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Renderer::isRunning() {
    return !glfwWindowShouldClose(window_);
}

bool Renderer::universeShouldMakeStep() {
    return getRuntime() * speedFactor_ > universePtr_->simuationTime_;
}
