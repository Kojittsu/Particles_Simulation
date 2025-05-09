#include "renderer.h"
#include <cmath>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Renderer::Renderer(const Config& config)
    : m_config(config), m_boxes(config.boxes), m_scaleFactor(config.scaleFactor) {
    m_quadric = gluNewQuadric();
    Camera m_camera;
    initializeGLFW();
    initializeImGui();
}

Renderer::~Renderer() {
    if (m_quadric) {
        gluDeleteQuadric(m_quadric);
    }
}

void Renderer::initializeGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    m_window = glfwCreateWindow(900, 600, "Particle System", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW Window.");
    }

    glfwMakeContextCurrent(m_window);

    // Associate actual instance to the window
    glfwSetWindowUserPointer(m_window, this);

    // Set framebuffer size callback
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* win, int width, int height) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->framebufferSizeCallback(width, height);
        }
    });

    // Set cursor callback 
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* win, double xpos, double ypos) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->cursorPosCallback(xpos, ypos);
        }
    });

    // Set key callback
    glfwSetKeyCallback(m_window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->keyboardCallback(key, scancode, action, mods);
        }
    });

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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
    
    m_camera.configurePerspective(aspectRatio);
    
    glMatrixMode(GL_MODELVIEW);
}

void Renderer::cursorPosCallback(double xpos, double ypos) {
    if(m_isSpectatorMode) {
        float xOffset = xpos - m_lastX;
        float yOffset = m_lastY - ypos; // Reverse the Y offset so that the upward movement is positive
        m_camera.computeNewOrientation(xOffset, yOffset);
    }

    m_lastX = xpos;
    m_lastY = ypos;
}

void Renderer::keyboardCallback(int key, int scancode, int action, int mods) {
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            m_keyStates[key] = true;
        } else if (action == GLFW_RELEASE) {
            m_keyStates[key] = false;
        }
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && m_isSpectatorMode) {
        toggleSpectatorMode();
    }
}

void Renderer::initializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    // ImGui/Glfw bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Renderer::render(const Universe& universe) {
    
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - m_lastFrameTime;
    
    // compute m_runTime & m_simulationTimePaused
    if(universe.m_isRunning) {
        m_runTime = currentFrame - m_simulationTimePaused;
    }
    else {
        m_simulationTimePaused += deltaTime;
    }

    // Update camera 
    if(m_isSpectatorMode) {
        m_camera.computeNewPosition(m_keyStates, deltaTime);
    }
    m_lastFrameTime = currentFrame;
    
    m_camera.update();

    const auto& particles = universe.getParticles();

    for (const auto& particle : particles) {
        auto position = particle.getPosition() * m_scaleFactor; // transform particle position from meter to SU
        auto color = particle.getColor();
        double radius = particle.getRadius() * m_scaleFactor; // transform particle radius from meter to SU

        // Define material properties
        GLfloat mat_diffuse[] = { color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, 1.0f };
        GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat mat_shininess[] = { 50.0f };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glPushMatrix();
        glTranslated(position[0], position[1], position[2]);
        gluSphere(m_quadric, radius, 16, 16);
        glPopMatrix();
    }
}

void Renderer::drawBoxes() {
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    for(Box& box : m_boxes) {
        std::array<double, 3> boxOrigin = box.m_origin  * m_scaleFactor; // transform box from meter to SU

        float x0 = boxOrigin[0];
        float y0 = boxOrigin[1];
        float z0 = boxOrigin[2];

        float x1 = x0 + box.m_length * m_scaleFactor; // transform box length from meter to SU
        float y1 = y0 + box.m_height * m_scaleFactor; // transform box height from meter to SU
        float z1 = z0 + box.m_depth * m_scaleFactor; // transform box depth from meter to SU
    
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

void Renderer::swapBuffers() {
    glfwSwapBuffers(m_window);
}


void Renderer::renderImGui(Universe& universe) {

    static bool showParticleConfig = false;
    static std::array<double, 3> position     = {0.0, 0.0, 0.0};
    static std::array<double, 3> velocity     = {0.0, 0.0, 0.0};
    static std::array<double, 3> acceleration = {0.0, 0.0, 0.0};
    static double radius = 0.0;
    static double mass   = 0.0;
    static std::array<int, 3> color = {0, 0, 0};

    // Start new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    // Set round corners
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

    if (ImGui::Button(universe.m_isRunning ? "Pause simulation" : "Start simulation")) {
        universe.m_isRunning = !universe.m_isRunning;
    }

    if (ImGui::Button("Toggle gravity")) {
        universe.toggleGravity();
    }
    ImGui::SameLine();
    ImGui::Text(universe.getIsGravity() ? "Gravity ON" : "Gravity OFF");

    if (ImGui::Button("Add particle")) {
        showParticleConfig = true;
    }

    bool isSpectatorMode = m_isSpectatorMode;
    if (ImGui::Checkbox("Spectator mode", &isSpectatorMode)) {
        toggleSpectatorMode();
    }

    static bool showWireframe = false;
    if (ImGui::Checkbox("Wireframe mode", &showWireframe)) {
        glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);
    }

    ImGui::PushItemWidth(100);
    static float cameraSpeedInSceneUnit = m_camera.getSpeed();
    static float cameraSpeedInMeters = cameraSpeedInSceneUnit / m_scaleFactor; // transform camera position from SU to meter
    if (ImGui::InputFloat("Set camera speed", &cameraSpeedInMeters, 0.0f, 0.0f, "%.3e m/s")) {
        cameraSpeedInSceneUnit = cameraSpeedInMeters * m_scaleFactor; // transform camera position from meter to SU
        m_camera.setSpeed(cameraSpeedInSceneUnit);
    }
    ImGui::PopItemWidth();

    ImGui::PushItemWidth(300);
    static glm::vec3 newCameraPositionInSceneUnit = m_camera.getPosition();
    static glm::vec3 newCameraPositionInMeters = newCameraPositionInSceneUnit / static_cast<float>(m_scaleFactor);  // transform camera position from SU to meter
    if(ImGui::InputFloat3("Set camera position", &newCameraPositionInMeters[0],"%.3e m")){
        newCameraPositionInSceneUnit = newCameraPositionInMeters * static_cast<float>(m_scaleFactor);  // transform camera position from meter to SU
        m_camera.setPosition(newCameraPositionInSceneUnit); 
    }
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::End();

    if (showParticleConfig) {
        ImGui::Begin("New particle configuration", &showParticleConfig, ImGuiWindowFlags_AlwaysAutoResize);
        
        ImGui::Text("Position:");
        ImGui::InputDouble("X (m)", &position[0]);
        ImGui::InputDouble("Y (m)", &position[1]);
        ImGui::InputDouble("Z (m)", &position[2]);

        ImGui::Text("Velocity:");
        ImGui::InputDouble("Vx (m/s)", &velocity[0]);
        ImGui::InputDouble("Vy (m/s)", &velocity[1]);
        ImGui::InputDouble("Vz (m/s)", &velocity[2]);

        ImGui::Text("Acceleration:");
        ImGui::InputDouble("Ax (m/s^2)", &acceleration[0]);
        ImGui::InputDouble("Ay (m/s^2)", &acceleration[1]);
        ImGui::InputDouble("Az (m/s^2)", &acceleration[2]);

        ImGui::Text("Radius:");
        ImGui::InputDouble("Radius (m)", &radius);

        ImGui::Text("Mass:");
        ImGui::InputDouble("Mass (Kg)", &mass);

        ImGui::Text("Color:");
        ImGui::SliderInt("R", &color[0], 0, 255);
        ImGui::SliderInt("G", &color[1], 0, 255);
        ImGui::SliderInt("B", &color[2], 0, 255);

        if (ImGui::Button("Confirm")) {
            Particle particle(position, velocity, acceleration, radius, mass, color);
            universe.addParticle(particle);
        }
        ImGui::End();
    }

    double totalSeconds = universe.m_simuationTime;
    int days    = static_cast<int>(totalSeconds / 86400);
    int hours   = static_cast<int>(static_cast<int>(totalSeconds) % 86400 / 3600);
    int minutes = static_cast<int>(static_cast<int>(totalSeconds) % 3600 / 60);
    int seconds = static_cast<int>(totalSeconds) % 60;

    glm::vec3 cameraPosition = m_camera.getPosition() / static_cast<float>(m_scaleFactor); // transform camera position from SU to meter
    glm::vec3 cameraFront = m_camera.getFront();
    glm::vec3 cameraUp = m_camera.getUp();

    ImGui::Begin("Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImGui::Text("Window size : %.0f x %.0f", windowSize.x, windowSize.y);
    ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);
    ImGui::Text(" ");
    ImGui::Text("Simulation time : %d days, %02d hours, %02d minutes, %02d seconds", days, hours, minutes, seconds);
    ImGui::Text("Simulation time : %.3f s", universe.m_simuationTime);
    ImGui::Text("Real time (s) : %.3f", m_runTime);
    ImGui::Text(" ");
    ImGui::Text("Camera position : (%.3e, %.3e, %.3e) m", cameraPosition[0], cameraPosition[1], cameraPosition[2]);
    ImGui::Text("Camera front : (%.1f, %.1f, %.1f)", cameraFront[0], cameraFront[1], cameraFront[2]);
    ImGui::Text("Camera up : (%.1f, %.1f, %.1f)", cameraUp[0], cameraUp[1], cameraUp[2]);
    ImGui::Text(" ");
    ImGui::Text("OpenGL version : %s", glGetString(GL_VERSION));
    ImGui::Text("ImGui version : %s", ImGui::GetVersion());
    ImGui::End();


    ImGui::Begin("Particles", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Particle count : %ld", universe.getParticles().size());
    ImGui::Text(" ");
    for (const Particle& particle : universe.getParticles()){
        ImGui::Text("Name : %s", particle.m_name.c_str());
        ImGui::Text("Position : (%.3e, %.3e, %.3e) m", particle.getX(), particle.getY(), particle.getZ());
        ImGui::Text("Velocity : (%.3e, %.3e, %.3e) m/s. %.3e m/s", particle.getVX(), particle.getVY(), particle.getVZ(), getMagnitude(particle.getVelocity()));
        ImGui::Text("Radius : %.3e m", particle.getRadius());
        ImGui::Text(" ");
    }
    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::toggleSpectatorMode() {
    m_isSpectatorMode = !m_isSpectatorMode;
    if (m_isSpectatorMode) {
       glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    }
    else {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Renderer::isRunning() {
    return !glfwWindowShouldClose(m_window);
}