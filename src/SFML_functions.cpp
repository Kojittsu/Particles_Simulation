#include "SFML_functions.h"

std::array<double, 2> Calculate_SFML_Coord(const double x, const double y, const Box &box, double scaleFactorPixels){
    std::array<double, 2> SFML_coord = {(x-box.getXOrigin()) * scaleFactorPixels, (box.getHeight()-(y-box.getYOrigin())) * scaleFactorPixels};
    return SFML_coord;
}

sf::VertexArray computeCircle(int windowLength, int windowHeight, int radius, int pointCount) {
    // Create array of vertices for lines
    sf::VertexArray circle(sf::LineStrip, pointCount + 1);

    // Center of the circle
    sf::Vector2f center(windowLength / 2, windowHeight / 2);

    for (int i = 0; i < pointCount; ++i) {
        float angle = i * 2 * M_PI / pointCount;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);

        circle[i].position = sf::Vector2f(x, y);
        circle[i].color = sf::Color::Red;
    }

    // Close the circle
    circle[pointCount].position = circle[0].position;
    circle[pointCount].color = sf::Color::Red;

    return circle;
}

static sf::Color getRainbow(float t) {
    const float r = sin(t);
    const float g = sin(t + 0.33f * 2.0f * M_PI);
    const float b = sin(t + 0.66f * 2.0f * M_PI);
    return {static_cast<uint8_t>(255.0f * r * r),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(255.0f * b * b)};
}

std::vector<std::vector<Coordinate>> readParticleMovements(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::map<int, std::vector<Coordinate>> particleMap;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 4) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue; // skip invalid lines
        }

        double time = std::stod(tokens[0]);
        int particleNumber = std::stoi(tokens[1]);
        double x = std::stod(tokens[2]);
        double y = std::stod(tokens[3]);

        Coordinate coord(time, x, y);
        particleMap[particleNumber].push_back(coord);
    }

    std::vector<std::vector<Coordinate>> particleMovements;
    for (auto& pair : particleMap) {
        particleMovements.push_back(std::move(pair.second));
    }

    return particleMovements;
}

void RenderParticleMovements(std::vector<std::vector<Coordinate>> particleMovements, Box box, Circle circle, std::vector<double> particlesRadius, double scaleFactorPixels){

    // Set window size
    int windowLength = std::floor(scaleFactorPixels*box.getLength());
    int windowHeight = std::floor(scaleFactorPixels*box.getHeight());

	// Create window
    sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "Particle Movement", sf::Style::None);

    // Create circle
    sf::VertexArray SFML_circle;
    if (circle.getRadius()){
        SFML_circle = computeCircle(windowLength, windowHeight, circle.getRadius()*scaleFactorPixels, 1000);
    }

    // Get number of particles
    int particleNumbers = particleMovements.size();

    // Creating vector of SFML radius particles
    std::vector<double> SFML_particleRadius;
    for (double& radius : particlesRadius){
        double SFML_radius = radius * scaleFactorPixels;
        SFML_particleRadius.push_back(SFML_radius);
    }

    // Create SFML particles
    std::vector<sf::CircleShape> particles;
    for (int i = 0; i < particleNumbers; ++i) {
        sf::CircleShape particle;
        particle.setRadius(SFML_particleRadius[i]);
        particle.setFillColor(getRainbow(i));
        particles.push_back(particle);
    }

    // Index vector for following particles position 
    std::vector<std::size_t> indexes(particleNumbers, 0);

    // Set SFML Clock
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Set SFML particle positions
        for (int i=0;i<particleNumbers;i++){
            // Get particle index
            std::size_t &index = indexes[i];
            
            // Get particle movement
            std::vector<Coordinate> particleMovement = particleMovements[i];

            // Update particle position depending on elapsed time
            if (index < particleMovement.size() && clock.getElapsedTime().asSeconds() >= particleMovement[index].time) {

                std::array<double, 2> SFML_coord = Calculate_SFML_Coord(particleMovement[index].x, particleMovement[index].y, box, scaleFactorPixels);
                
                // Set the position of the SFML particle and offset it because the SFML setPosition() 
                // function sets the upper left corner of the circle to the position provided.
                particles[i].setPosition(SFML_coord[0]-SFML_particleRadius[i], SFML_coord[1]-SFML_particleRadius[i]);

                index++;
            }
        }

        window.clear();

        // Draw particles
        for (sf::CircleShape particle : particles){window.draw(particle);}

        // Draw circle
        if (circle.getRadius()){window.draw(SFML_circle);}

        window.display();
    }
}