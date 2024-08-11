#include "textBox.hpp"

textBox::textBox(const int CharacterSize, const sf::Vector2f& position, const std::string& text, const sf::Color& textColor) {
    
    if (!m_font.loadFromFile("Roboto-Regular.ttf")) {
        throw std::runtime_error("Impossible de charger la police Roboto-Regular.ttf");
    }

    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(CharacterSize);
    m_text.setFillColor(textColor);

    m_text.setPosition(position.x, position.y);
}