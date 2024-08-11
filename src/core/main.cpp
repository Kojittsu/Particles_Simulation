#include "universe.h"
#include "renderer.hpp"
#include "button.hpp"

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

    // Set window size
    int windowLength = std::floor(config.scaleFactorPixels * universe.m_boxLength);
    int windowHeight = std::floor(config.scaleFactorPixels * universe.m_boxHeight);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    
    sf::RenderWindow window(sf::VideoMode(windowLength, windowHeight), "Verlet", sf::Style::None, settings);

    Renderer renderer(window);

    // Set SFML Clock
    sf::Clock clock;
    sf::Time elapsedTime = sf::Time::Zero;

    // Play / Pause button
    Button PlayPause(
        sf::Vector2f(100, 20),
        sf::Vector2f(10, 50),
        "Play / Pause",
        [&universe, &clock, &elapsedTime]() { 
            universe.m_isRunning = !universe.m_isRunning; 
            if (universe.m_isRunning) {
                clock.restart();
            } else {
                elapsedTime += clock.getElapsedTime();
            }
        }
    );

    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            PlayPause.handleEvent(event);
        }

        if (universe.m_isRunning) {
            if ((elapsedTime + clock.getElapsedTime()).asSeconds() * config.speedFactor > universe.m_runTime) {
                
                universe.makeStep();

                window.clear(sf::Color::Black);
                renderer.render(universe);
                PlayPause.draw(window);
                window.display();

                if (file.is_open()) {
                    universe.saveStep(file, stepNumberSaved);
                    stepNumberSaved++;
                }
            }
        }
        else {
            window.clear(sf::Color::Black);
            renderer.render(universe);
            PlayPause.draw(window);
            window.display();
        }
    }

    if (file.is_open()) { file.close(); }

    return 0;
}
