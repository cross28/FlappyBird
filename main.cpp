#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bird.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow&, sf::View&);

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Practice", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)); //Camera follows bird

    float deltaTime = 0.0f;
    sf::Clock clock;

    sf::Texture birdTexture;
    birdTexture.loadFromFile("images/redbird-upflap.png");

    Bird bird(&birdTexture, sf::Vector2u(1, 1), 0.4f, 20.0f, 20.0f);

    while (window.isOpen()){

        deltaTime = clock.restart().asSeconds();
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


        bird.update(deltaTime);
        view.setCenter(bird.getPosition());
        window.clear(sf::Color::Black);
        window.setView(view);
        bird.draw(window);
        window.display();
    }

    return 0;
}

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);

    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
