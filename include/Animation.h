#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

/**
* This class will handle all of the movement for the sprites
**/

class Animation
{
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float switchTime;
    float totalTime;

public:
    Animation(sf::Texture *texture, sf::Vector2u imageCOunt, float switchTime);
    virtual ~Animation();

    void update(int row, float deltaTime);
    sf::IntRect textureRect;
};

#endif // ANIMATION_H
