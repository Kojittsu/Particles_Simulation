#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, std::function<void()> onClick);

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Font m_font;
    std::function<void()> m_onClick;
};

#endif