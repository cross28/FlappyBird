#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{
private:
    sf::RectangleShape body;

public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    virtual ~Platform();

    void draw(sf::RenderWindow& window);
    Collider getCollider() { return Collider(body); }
};

#endif // PLATFORM_H
