#include "renderer.hpp"

Renderer::Renderer(sf::RenderTarget& target)
    : m_target(target)
    {}

void Renderer::render(const Universe& universe) const {

    // Load font
    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    // Create text object for displaying simulation time
    sf::Text currentTimeText;
    currentTimeText.setFont(font);
    currentTimeText.setCharacterSize(16);
    currentTimeText.setFillColor(sf::Color::Blue);
    currentTimeText.setPosition(10, 10); // Position at the top-left corner

    // Render constraint
    if(universe.circleRadius != 0){
        std::array<double, 2> s_center = s_coordinates(universe.circleX, universe.circleY, universe);
        double s_circleRadius = universe.circleRadius * universe.scaleFactorPixels;
        sf::CircleShape constraint_background(s_circleRadius);
        constraint_background.setOrigin(s_circleRadius, s_circleRadius);
        constraint_background.setFillColor(sf::Color::White);
        constraint_background.setPosition(s_center[0], s_center[1]);
        constraint_background.setPointCount(128);
        m_target.draw(constraint_background);
    }

    //Render objects
    const std::vector<Particle>& particles = universe.getParticles();

    sf::CircleShape s_particle{1.0f};
    s_particle.setPointCount(32);
    s_particle.setOrigin(1.0f, 1.0f);
    
    for (const Particle& particle : particles) {

        // Get particle infos
        double radius = particle.getRadius();
        std::array<double, 2> position = particle.getPosition();

        // Get particle color
        std::array<int, 3> color = particle.getColor();
        
        // Transform in SFML coordinates
        std::array<double, 2> s_position = s_coordinates(position[0], position[1], universe);
        double s_radius = radius * universe.scaleFactorPixels;

        // make particle singular pixel if radius too small to render
        if (s_radius < 1){s_radius=1;}

        s_particle.setPosition(s_position[0], s_position[1]);
        s_particle.setScale(s_radius, s_radius);
        s_particle.setFillColor(sf::Color(color[0], color[1], color[2]));
        m_target.draw(s_particle);
    }

    // Update the simulation time text
    currentTimeText.setString("simulation time : " + formatedTime(universe.runTime));

    // Draw the simulation time text
    m_target.draw(currentTimeText);
}

std::array<double, 2> Renderer::s_coordinates(const double x, const double y, const Universe& universe) const {
    std::array<double, 2> s_coord = {
        (x - universe.boxOriginX) * universe.scaleFactorPixels,
        (universe.boxHeight - (y - universe.boxOriginY)) * universe.scaleFactorPixels
    };
    return s_coord;
}