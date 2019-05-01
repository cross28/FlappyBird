#include "Bird.h"
#include "math.h"

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

    std::ifstream ifs("/home/cross/Documents/C++/2D SFML Game/stats/stat.txt");
    ifs >> lifeTimeScore;
    ifs >> deaths;
    ifs.close();
}

Bird::~Bird()
{

}

void Bird::update(float deltaTime)
{
    velocity.y *= 0.74f;

    //Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump==true) {
        velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
    }

    if (isDead==false) {
        velocity.y += 250 * GRAVITY * deltaTime;
    }

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

    //Collision on the right, bottom, top
    if (direction.x < 0.0f || direction.x > 0.0f || direction.y > 0.0f || direction.y < 0.0f) {
        setVelocity(0.0f, 0.0f);
        setJump(false);
    }
}

float Bird::getRatio()
{
    if (deaths == 0)
        sdRatio = lifeTimeScore;
    else
        sdRatio = lifeTimeScore / deaths;
}

void Bird::incScore()
{
    try {
        std::ofstream ifs("/home/cross/Documents/C++/2D SFML Game/stats/stat.txt", std::ios_base::out);
        lifeTimeScore++;
        ifs << lifeTimeScore << std::endl;
        ifs.close();
    }
    catch (std::exception e) {
        std::cout << "Error: Couldn't save to file." << std::endl;
    }
}

void Bird::incDeath()
{
    try {
        std::ofstream ifs("/home/cross/Documents/C++/2D SFML Game/stats/stat.txt", std::ios_base::out);
        deaths++;
        ifs << lifeTimeScore << std::endl;
        ifs << deaths << std::endl;;
        ifs.close();
    }
    catch (std::exception e) {
        std::cout << "Error: Couldn't save to file." << std::endl;
    }
}
