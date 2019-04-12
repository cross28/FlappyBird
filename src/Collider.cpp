#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) :
    body(body)
{

}

Collider::~Collider()
{

}

bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, bool isDead = false)
{
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        isDead = true;
        return true;
    }

    return false;
}
