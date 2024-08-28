#include "universe.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>  // Include GLU in order to use gluPerspective
#include <vector>

// Callback to resize window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);
    
    // Configure 45 degrees view angle perspective
    gluPerspective(45.0, aspectRatio, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
}

void renderParticles(const std::vector<Particle>& particles) {
    GLUquadric* quad = gluNewQuadric();

    for (const auto& particle : particles) {
        std::array<double, 3> position = particle.getPosition();
        std::array<int, 3> color = particle.getColor();
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
        gluSphere(quad, radius, 32, 32); // Raise up segments for more details
        glPopMatrix();
    }
    gluDeleteQuadric(quad);
}

void drawBox(double xOrigin, double yOrigin, double zOrigin, double length, double height, double depth) {
    float x0 = xOrigin;
    float y0 = yOrigin;
    float z0 = zOrigin;
    
    float x1 = x0 + length;
    float y1 = y0 + height;
    float z1 = z0 + depth;

    glBegin(GL_LINES);

    // Front panel vertices (z = z0)
    glVertex3f(x0, y0, z0); glVertex3f(x1, y0, z0);
    glVertex3f(x1, y0, z0); glVertex3f(x1, y1, z0);
    glVertex3f(x1, y1, z0); glVertex3f(x0, y1, z0);
    glVertex3f(x0, y1, z0); glVertex3f(x0, y0, z0);

    // Back panel vertices (z = z1)
    glVertex3f(x0, y0, z1); glVertex3f(x1, y0, z1);
    glVertex3f(x1, y0, z1); glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z1); glVertex3f(x0, y1, z1);
    glVertex3f(x0, y1, z1); glVertex3f(x0, y0, z1);

    // Vertices connecting front and back panels
    glVertex3f(x0, y0, z0); glVertex3f(x0, y0, z1);
    glVertex3f(x1, y0, z0); glVertex3f(x1, y0, z1);
    glVertex3f(x1, y1, z0); glVertex3f(x1, y1, z1);
    glVertex3f(x0, y1, z0); glVertex3f(x0, y1, z1);

    glEnd();
}

int main(int argc, char* argv[]) {
    
    // Check if the configuration file name is provided
    if (argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    const std::string configFile = argv[1];

    // Read configuration
    Config config;
    if (!readConfig(configFile, config)) {
        return 1;
    }

    // Create universe
    Universe universe(config);

    // Open dataFile if dataFileName provided
    std::ofstream file;
    if (!config.dataFileName.empty()) {
        file.open(config.dataFileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << config.dataFileName << std::endl;
            return 1;
        }
    }
    int stepNumberSaved = 0;

    // GLFW init
    if (!glfwInit()) {
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(900, 600, "Particle System", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Set light number 0

    // Configure light properties
    GLfloat light_pos[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Set GLFW time to zero
    glfwSetTime(0.0);
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        
        if (currentTime * config.speedFactor > universe.m_runTime) {
            
            universe.makeStep();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            gluLookAt(0.0, 0.0, 50.0,  // camera position
                      0.0, 0.0, 0.0,   // Where the camera looks
                      0.0, 1.0, 0.0);  // Camera orientation (upwards)

            renderParticles(universe.getParticles());

            drawBox(config.boxOriginX, config.boxOriginY, config.boxOriginZ, config.boxLength, config.boxHeight, config.boxDepth);

            glfwSwapBuffers(window);
            glfwPollEvents();

            if (file.is_open()) {
                universe.saveStep(file, stepNumberSaved);
                stepNumberSaved++;
            }
        }
    }

    glfwTerminate();

    if (file.is_open()) { file.close(); }
    
    return 0;

}
