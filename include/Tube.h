#ifndef TUBE_H
#define TUBE_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Tube
{
private:
    sf::RectangleShape body;

public:
    Tube(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    virtual ~Tube();

    void draw(sf::RenderWindow& window);
    Collider getCollider() { return Collider(body); }
};

#endif // TUBE_H
