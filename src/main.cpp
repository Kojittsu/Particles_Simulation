#include "universe.h"
#include "renderer.hpp"

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

    // Add random particles to universe
    for(int i=0; i< config.rndParticle_numbers; i++){
        universe.addRndParticle(config.rndParticle_maxVelocityX, config.rndParticle_maxVelocityY, config.rndParticle_minRadius, config.rndParticle_maxRadius, config.rndParticle_minMass, config.rndParticle_maxMass);
    }

    // Open file
    std::ofstream file;
    if (!config.dataFileName.empty()) {
        file.open(config.dataFileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << config.dataFileName << std::endl;
            return 1;
        }
    }

    int stepNumberSaved = 0;
    
    // Apply global acceleration
    universe.applyAccelerationToParticles(config.globalAcceleration);

    // Set window size
    int windowLength = std::floor(config.scaleFactorPixels * universe.getBox().getLength());
    int windowHeight = std::floor(config.scaleFactorPixels * universe.getBox().getHeight());

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    
    sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "Verlet", sf::Style::None, settings);

    Box box_test = universe.getBox();
    Renderer renderer(window, box_test, config.scaleFactorPixels);

    // Set SFML Clock
    sf::Clock clock;

    // // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if(clock.getElapsedTime().asSeconds() * config.speedFactor > universe.getRunTime()){
            universe.makeStep();
            window.clear(sf::Color::Black);
            renderer.render(universe);
            window.display();

            universe.setRunTime(universe.getRunTime() + config.deltaTime);

            if (file.is_open()){
                universe.saveStep(file, stepNumberSaved);
                stepNumberSaved++;
            }
        }
    }
    if (file.is_open()) {file.close();}

    return 0;
}
