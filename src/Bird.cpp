#include "Bird.h"
#include "math.h"
#include <iostream>

static const float GRAVITY = 981.0f;

Bird::Bird(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float velX, float jumpHeight) :
    animation(texture, imageCount, switchTime)
{
    this->velocity.x = velX;
    this->jumpHeight = jumpHeight;
    row = 0;

    body.setSize(sf::Vector2f(50.0f, 50.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(200.0f, 200.0f);
    body.setTexture(texture);
}

Bird::~Bird()
{

}

void Bird::update(float deltaTime)
{
    velocity.y *= 0.74f;

    //Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
        velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
    }

     //Multiplier is arbitrary
    velocity.y += 250 * GRAVITY * deltaTime;

    animation.update(row, deltaTime);
    body.setTextureRect(animation.textureRect);
    body.move(velocity * deltaTime);
}
void Bird::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Bird::onCollision(sf::Vector2f direction)
{
    isDead = true;

    //Collision on the right
    if (direction.x > 0.0f) {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }

    //Collision on the bottom
    if (direction.y > 0.0f) {
        //velocity.x = 0.0f;
        //velocity.y = 0.0f;
    }

    //Collision on the top
    if (direction.y < 0.0f) {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }
}
