#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "universe.h"
#include "textBox.hpp"


class Renderer {
public:
    Renderer(sf::RenderTarget& target);

    void render(const Universe& universe);
    std::array<double, 2> s_coordinates(double x, double y, const Universe& universe) const;

private:
    sf::RenderTarget& m_target;
    sf::Font m_font;
    sf::Text m_currentTimeText;
};

#endif