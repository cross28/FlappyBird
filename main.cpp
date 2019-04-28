#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Bird.h"
#include "Button.h"
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
    Bird bird(&birdTexture, sf::Vector2u(1, 1), 0.3f, 200.0f, 200.0f);

    std::vector<Platform> tubes;
    sf::Texture tubeTop;
    tubeTop.loadFromFile("images/tube.png");
    tubes.push_back(Platform(&tubeTop, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    tubes.push_back(Platform(&tubeTop, sf::Vector2f(100.0f, 200.0f), sf::Vector2f(500.0f,800.0f)));

    while (window.isOpen()){
        const float FPS = 1 / 30.0f;
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > FPS)
            deltaTime = FPS;

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
            }
        }



        Collider bgc = bird.getCollider();
        for (Platform& tube : tubes) {
        sf::Vector2f direction;
            if (tube.getCollider().checkCollision(bgc, direction, 1.0f)) {
                bird.onCollision(direction);
            }
        }

        //Set camera view
        view.setCenter(bird.getPosition());
        window.setView(view);

        window.clear();

        //Draw the sprites
        bird.update(deltaTime);
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
