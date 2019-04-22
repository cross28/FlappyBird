#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Bird.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow&, sf::View&);

int main(){
    sf::RenderWindow window(sf::VideoMode(512, 512), "Practice", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)); //Camera follows bird

    float deltaTime = 0.0f;
    sf::Clock clock;

    sf::Texture birdTexture;
    birdTexture.loadFromFile("images/redbird-upflap.png");
    Bird bird(&birdTexture, sf::Vector2u(1, 1), 0.3f, 100.0f, 200.0f);

    std::vector<Platform> tubes;
    sf::Texture longTubeTop;
    longTubeTop.loadFromFile("images/LongTubeTop.png");
    tubes.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
    tubes.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    tubes.push_back(Platform(&longTubeTop, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(500.0f,800.0f)));

    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 30.0f)
            deltaTime = 1.0f/ 30.0f;

        sf::Event evnt;

        while(window.pollEvent(evnt)){
            switch(evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            //Keeps the sprites scaled properly
            case sf::Event::Resized:
                ResizeView(window, view);
                break;

            /*
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Space)
                    bird.setJump(false);
                break;

            case sf::Event::KeyReleased:
                bird.setJump(true);
                break;
            */
            }
        }


        bird.update(deltaTime);
        sf::Vector2f direction;
        Collider bgc = bird.getCollider();
        for (Platform& tube : tubes) {
            if (tube.getCollider().checkCollision(bgc, direction, 1.0f)) {
                bird.onCollision(direction);
                bird.setVelocity(0.0f, 0.0f);
            }
        }
        view.setCenter(bird.getPosition());
        window.clear();
        window.setView(view);
        bird.draw(window);
        for (Platform& tube : tubes)
            tube.draw(window);
        window.display();
    }

    return 0;
}

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);

    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
