#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

enum button_states{btn_idle = 0, btn_hover, btn_active};

class Button
{
private:
    short unsigned buttonState;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    Button(float x, float y, float width, float height, sf::Font* font,
            std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    virtual ~Button();

    const bool isPressed() const;

    void draw(sf::RenderWindow& window);
    void update(const sf::Vector2f mousePos);
};

#endif // BUTTON_H
