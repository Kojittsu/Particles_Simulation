#include <SFML/Graphics.hpp>

class textBox {
public:
    textBox(const int CharacterSize, const sf::Vector2f& position, const std::string& text, const sf::Color& textColor);
    sf::Text m_text;
    sf::Font m_font;
};
