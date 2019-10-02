#include "../include/Tube.h"

Tube::Tube(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
}

Tube::~Tube()
{

}

void Tube::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::Vector2f Tube::getPosition()
{
    return body.getPosition();
}
