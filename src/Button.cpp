#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = btn_idle;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(12);
    this->text.setPosition(this->shape.getPosition().x / 2.0f - this->text.getGlobalBounds().width / 2.0f,
                           this->shape.getPosition().y / 2.0f - this->text.getGlobalBounds().height / 2.0f);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

const bool Button::isPressed() const {
    if (this->buttonState == btn_active)
        return true;

    return false;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Button::update(const sf::Vector2f mousePos) {

    /**Updating whether the mouse does any actions over the button**/

    //Idle
    this->buttonState = btn_idle;

    //Hover
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonState = btn_hover;

        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->buttonState = btn_active;
        }
    }

    //Changing their respective colors
    switch(this->buttonState)
    {
    case btn_idle:
        this->shape.setFillColor(idleColor);
        break;

    case btn_hover:
        this->shape.setFillColor(hoverColor);
        break;

    case btn_active:
        this->shape.setFillColor(activeColor);
        break;
    }
}
