#include "Bird.h"
#include "math.h"

static const float GRAVITY = 981.0f;

Bird::Bird(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    row = 0;

    body.setSize(sf::Vector2f(100.0f, 100.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(100.0f, 100.0f);
    body.setTexture(texture);
}

Bird::~Bird()
{

}

void Bird::update(float deltaTime)
{
    velocity.y = 0.0f;
    velocity.x = 20.0f;

    //Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);

    velocity.y += GRAVITY * jumpHeight;

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
    //Collision on the right
    if (direction.x > 0.0f) {
        velocity.x = 0.0f;
        isDead = true;
    }
    //Collision on the bottom
    if (direction.y > 0.0f) {
        velocity.x = 0.0f;
        isDead = true;
    }
    //Collision on the top
    if (direction.y < 0.0f) {
        velocity.x = 0.0f;
        isDead = true;
    }
}
