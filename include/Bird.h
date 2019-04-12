#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Bird
{
private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;

public:
    Bird(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    virtual ~Bird();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() { return body.getPosition(); }

};

#endif // BIRD_H
