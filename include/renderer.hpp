#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "universe.h"
#include "box.h"


class Renderer {
public:
    Renderer(sf::RenderTarget& target, const Box& box, double scaleFactorPixels);

    void render(const Universe& universe) const;
    std::array<double, 2> s_coordinates(double x, double y) const;

private:
    sf::RenderTarget& m_target;
    const Box& m_box;
    const double m_scaleFactorPixels;
};

#endif