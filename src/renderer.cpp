#include "renderer.hpp"
#include <stdexcept>

// Constructor
Renderer::Renderer(sf::RenderTarget& target)
    : m_target(target)
{
    // Load font once in constructor
    if (!m_font.loadFromFile("Roboto-Regular.ttf")) {
        throw std::runtime_error("Error loading font");
    }
    
    // Initialize text object for displaying simulation time
    m_currentTimeText.setFont(m_font);
    m_currentTimeText.setCharacterSize(16);
    m_currentTimeText.setFillColor(sf::Color::Blue);
    m_currentTimeText.setPosition(10, 10); // Position at the top-left corner
}

void Renderer::render(const Universe& universe) {
    // Render constraint
    if(universe.m_circleRadius != 0) {
        std::array<double, 2> s_center = s_coordinates(universe.m_circleX, universe.m_circleY, universe);
        double s_circleRadius = universe.m_circleRadius * universe.m_scaleFactorPixels;
        sf::CircleShape constraint_background(s_circleRadius);
        constraint_background.setOrigin(s_circleRadius, s_circleRadius);
        constraint_background.setFillColor(sf::Color::White);
        constraint_background.setPosition(s_center[0], s_center[1]);
        constraint_background.setPointCount(128);
        m_target.draw(constraint_background);
    }

    // Render objects
    const std::vector<Particle>& particles = universe.getParticles();

    sf::CircleShape s_particle{1.0f};
    s_particle.setPointCount(32);
    s_particle.setOrigin(1.0f, 1.0f);

    for (const Particle& particle : particles) {
        // Get particle infos
        double radius = particle.getRadius();
        const std::array<double, 2>& position = particle.getPosition();
        const std::array<int, 3>& color = particle.getColor();

        // Transform in SFML coordinates
        std::array<double, 2> s_position = s_coordinates(position[0], position[1], universe);
        double s_radius = radius * universe.m_scaleFactorPixels;

        // Make particle singular pixel if radius too small to render
        if (s_radius < 1) { s_radius = 1; }

        s_particle.setPosition(s_position[0], s_position[1]);
        s_particle.setScale(s_radius, s_radius);
        s_particle.setFillColor(sf::Color(color[0], color[1], color[2]));
        m_target.draw(s_particle);
    }

    // Update the simulation time text
    m_currentTimeText.setString("simulation time : " + formatedTime(universe.m_runTime));

    // Draw the simulation time text
    m_target.draw(m_currentTimeText);
}

std::array<double, 2> Renderer::s_coordinates(const double x, const double y, const Universe& universe) const {
    return {
        (x - universe.m_boxOriginX) * universe.m_scaleFactorPixels,
        (universe.m_boxHeight - (y - universe.m_boxOriginY)) * universe.m_scaleFactorPixels
    };
}
