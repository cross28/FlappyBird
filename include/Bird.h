#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Animation.h"
#include "Collider.h"

class Bird
{
private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    sf::Vector2f velocity;
    bool canJump=true;
    bool isDead = false;
    float jumpHeight;
    int lifeTimeScore;
    int deaths;
    float sdRatio = getRatio();

public:
    Bird(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
    virtual ~Bird();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    bool getBirdState() { return isDead; }
    void setJump(bool b) { canJump = b; }
    void setVelocity(float dx, float dy) { velocity.x = dx; velocity.y = dy; }
    void incScore();
    void incDeath();
    float getRatio();

    sf::Vector2f getPosition() { return body.getPosition(); }
    Collider getCollider() { return Collider(body); }

    void onCollision (sf::Vector2f direction);

};

#endif // BIRD_H
