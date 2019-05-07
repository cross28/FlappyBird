#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Bird.h"
#include "Tube.h"

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow&, sf::View&);

int main(){
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Practice", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)); //Camera follows bird

    float deltaTime = 0.0f;
    sf::Clock clock;

    sf::Texture background;
    background.loadFromFile("images/background.png");
    background.setRepeated(true);
    sf::Sprite bg(background);
    bg.setTextureRect(sf::IntRect(0, 0, 2000, 240));

    sf::Texture birdTexture;
    birdTexture.loadFromFile("images/redbird-upflap.png");
    Bird bird(&birdTexture, sf::Vector2u(1, 1), 0.3f, 100.0f, 50.0f, sf::Vector2f(0.0f, 0.0f));


    std::vector<Tube> tubes;
    sf::Vector2f tubeSize(100.0f, 500.0f);
    sf::Texture tubeTop;
    tubeTop.loadFromFile("images/tube.png");
    tubes.push_back(Tube(&tubeTop, tubeSize, sf::Vector2f(500.0f, 0.0f)));
    tubes.push_back(Tube(&tubeTop, tubeSize, sf::Vector2f(500.0f,800.0f)));
    tubes.push_back(Tube(&tubeTop, tubeSize, sf::Vector2f(1000.0f, 0.0f)));
    tubes.push_back(Tube(&tubeTop, tubeSize, sf::Vector2f(1000.0f, 800.0f)));

    while (window.isOpen()){
        const float FPS = 1 / 60.0f;
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > FPS)
            deltaTime = FPS;

        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch(evnt.type)
            {
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Escape)
                    window.close();
                if (evnt.key.code == sf::Keyboard::Space)
                    bird.setJump(false);
                break;

            case sf::Event::KeyReleased:
                if (evnt.key.code == sf::Keyboard::Space)
                    bird.setJump(true);
                break;

            case sf::Event::Closed:
                window.close();
                break;

            //Keeps the sprites scaled properly
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        window.clear();

        //Sprite drawing
        for (Tube& tube : tubes) {
            sf::Vector2f direction;
            Collider bgc = bird.getCollider();
            if (tube.getCollider().checkCollision(bgc, direction, 1.0f)) {
                bird.onCollision(direction);
            }

            if (bird.getPosition().x == tube.getPosition().x)
                bird.incScore();

            tube.draw(window);
        }

        //Set camera view
        view.setCenter(bird.getPosition());
        window.setView(view);
        bird.update(deltaTime);
        bird.draw(window);

        window.display();
    }

    return 0;
}

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);

    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
