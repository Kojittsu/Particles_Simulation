#include "button.hpp"


Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, std::function<void()> onClick)
    :
      m_onClick(onClick)
{
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::White);

    if (!m_font.loadFromFile("Roboto-Regular.ttf")) {
        throw std::runtime_error("Error loading font");
    }

    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(15);
    m_text.setFillColor(sf::Color::Black);
    m_text.setOrigin(
        m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2.0f, 
        m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2.0f
    );
    m_text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);

}

void Button::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
    window.draw(m_text);
}

void Button::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (m_shape.getGlobalBounds().contains(mousePos)) {
            m_onClick();
        }
    }
}