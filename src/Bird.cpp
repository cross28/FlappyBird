#include "Bird.h"

Bird::Bird(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;

    body.setSize(sf::Vector2f(100.0f, 100.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(200.0f, 200.0f);
    body.setTexture(texture);
}

Bird::~Bird()
{

}

void Bird::update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    //Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        movement.y -= speed * deltaTime;

    if (movement.y < 0.0f)
        row = 1;

    animation.update(row, deltaTime);
    body.setTextureRect(animation.textureRect);
    body.move(movement);
}

void Bird::draw(sf::RenderWindow& window)
{
    window.draw(body);
}
