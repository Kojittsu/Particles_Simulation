#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "universe.h"


class Renderer {
public:
    Renderer(sf::RenderTarget& target, double scaleFactorPixels);

    void render(const Universe& universe) const;
    std::array<double, 2> s_coordinates(double x, double y, const Universe& universe) const;

private:
    sf::RenderTarget& m_target;
    const double m_scaleFactorPixels;
};

#endif