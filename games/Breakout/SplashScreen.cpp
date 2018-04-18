#include "headers.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& window)
{
    sf::Texture texture;
    if(texture.loadFromFile("images/SplashScreen.png") != true)
    {
        return;
    }

    sf::Sprite sprite(texture);

    window.draw(sprite);
    window.display();

    sf::Event event;
    while(true)
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::EventType::KeyPressed
            || event.type == sf::Event::EventType::MouseButtonPressed
            || event.type == sf::Event::EventType::Closed)
            {
                return;
            }     
        }
    }
}
