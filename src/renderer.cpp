#include "renderer.h"
#include <cmath>

Renderer::Renderer(GLFWwindow* window, const Config& config)
    : m_config(config), m_quadric(nullptr) {
    m_quadric = gluNewQuadric();

    glfwMakeContextCurrent(window);

    // Associate actual instance to the window
    glfwSetWindowUserPointer(window, this);

    // Wrapper pour framebufferSizeCallback
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->framebufferSizeCallback(win, width, height);
        }
    });

    // Wrapper pour cursorPosCallback
    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->cursorPosCallback(win, xpos, ypos);
        }
    });

    // Wrapper pour keyCallback
    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
        if (renderer) {
            renderer->keyCallback(win, key, scancode, action, mods);
        }
    });

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glfwSetTime(0.0);
}

Renderer::~Renderer() {
    if (m_quadric) {
        gluDeleteQuadric(m_quadric);
    }
}

// Callback to resize window
void Renderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);
    
    // Configure 45 degrees view angle perspective
    gluPerspective(45.0, aspectRatio, m_minRenderDistance, m_maxRenderDistance);
    
    glMatrixMode(GL_MODELVIEW);
}

void Renderer::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {

    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // Reverse the Y offset so that the upward movement is positive

    m_lastX = xpos;
    m_lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_azimuth += xoffset;
    m_elevation += yoffset;

    if (m_elevation > 89.0f) m_elevation = 89.0f;
    if (m_elevation < -89.0f) m_elevation = -89.0f;

    float azimuthRad = glm::radians(m_azimuth);
    float elevationRad = glm::radians(m_elevation);

    m_cameraFront = glm::normalize(glm::vec3(
        cos(elevationRad) * cos(azimuthRad),
        sin(elevationRad),
        cos(elevationRad) * sin(azimuthRad)
    ));

    m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
}


void Renderer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key >= 0 && key < 1024) { // Vérifie que la touche est dans les limites
        if (action == GLFW_PRESS) {
            m_keyStates[key] = true;
        } else if (action == GLFW_RELEASE) {
            m_keyStates[key] = false;
        }
    }
}

void Renderer::processInput() {

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - m_lastFrameTime;
    m_lastFrameTime = currentFrame;
    float velocity = m_cameraSpeed * deltaTime;

    if (m_keyStates[GLFW_KEY_W]) {
        m_cameraPosition += m_cameraFront * velocity;
    }
    if (m_keyStates[GLFW_KEY_S]) {
        m_cameraPosition -= m_cameraFront * velocity;
    }
    if (m_keyStates[GLFW_KEY_A]) {
        m_cameraPosition -= m_cameraRight * velocity;
    }
    if (m_keyStates[GLFW_KEY_D]) {
        m_cameraPosition += m_cameraRight * velocity;
    }
    if (m_keyStates[GLFW_KEY_SPACE]) {
        m_cameraPosition += m_cameraUp * velocity;
    }
    if (m_keyStates[GLFW_KEY_LEFT_SHIFT]) {
        m_cameraPosition -= m_cameraUp * velocity;
    }
}


void Renderer::updateCameraView() {
    glLoadIdentity();

    glm::vec3 cameraTarget = m_cameraPosition + m_cameraFront;

    gluLookAt(
        m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z, // Position de la caméra
        cameraTarget.x, cameraTarget.y, cameraTarget.z,             // Point ciblé par la caméra
        m_cameraUp.x, m_cameraUp.y, m_cameraUp.z                    // Vecteur "Up"
    );
}



void Renderer::render(const Universe& universe) {

    const auto& particles = universe.getParticles();

    for (const auto& particle : particles) {
        auto position = particle.getPosition();
        auto color = particle.getColor();
        double radius = particle.getRadius();

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

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawBox() {
    float x0 = m_config.boxOriginX;
    float y0 = m_config.boxOriginY;
    float z0 = m_config.boxOriginZ;

    float x1 = x0 + m_config.boxLength;
    float y1 = y0 + m_config.boxHeight;
    float z1 = z0 + m_config.boxDepth;

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

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

    glEnable(GL_LIGHTING);
}
