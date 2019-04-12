#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics.hpp>

class Collider
{
private:
    sf::RectangleShape& body;

public:
    Collider(sf::RectangleShape& body);
    virtual ~Collider();

    void move(float dx, float dy) { body.move(dx, dy); }
    bool checkCollision(Collider& other, sf::Vector2f& direction, bool isDead);
    sf::Vector2f getPosition() { return body.getPosition(); }
    sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; }
};

#endif // COLLIDER_H
