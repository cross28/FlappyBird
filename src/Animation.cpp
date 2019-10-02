#include "../include/Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    textureRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
    textureRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
}

Animation::~Animation()
{

}

void Animation::update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime){
        totalTime -= switchTime;

        currentImage.x++;
        if (currentImage.x >= imageCount.x)
            currentImage.x = 0;
    }

    //Setting the top and left offsets for the sprite
    textureRect.top = currentImage.y * textureRect.height;
}
