#include <SFML/Graphics.hpp>
#include <iostream>

static const float VIEW_HEIGHT = 1000.0f;

void ResizeView(const sf::RenderWindow&, sf::View&);

int main(){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Practice", sf::Style::Titlebar | sf::Style::Close | sf::Style::Default);

    //Camera follows our player
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    float deltaTime = 0.0f;
    sf::Clock clock;


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


        window.clear(sf::Color::Red);
        window.setView(view);
        window.display();

    }

    return 0;
}

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);

    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
