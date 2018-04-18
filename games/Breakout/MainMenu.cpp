#include "headers.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    sf::Texture texture;
    texture.loadFromFile("images/mainmenu.png");
    sf::Sprite sprite(texture);

    MenuItem playButton;
    playButton.rect.top = 145;
    playButton.rect.height = 380;
    playButton.rect.left = 0;
    playButton.rect.width = 1023;
    playButton.action = Play;

    MenuItem exitButton;
    exitButton.rect.top = 383;
    exitButton.rect.height = 560;
    exitButton.rect.left = 0;
    exitButton.rect.width = 1023;
    exitButton.action = Exit;

    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);

    window.draw(sprite);
    window.display();

    return GetMenuResponse(window);
} 

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;

    for (it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::Rect<int> menuItemRect = (*it).rect;
        if (menuItemRect.height > y
         && menuItemRect.top < y
         && menuItemRect.left < x
         && menuItemRect.width > y)
        {
            return (*it).action;
        }
    }

    return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow &window)
{
    sf::Event event;

    while(true)
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                return HandleClick(event.mouseButton.x, event.mouseButton.y);
            }
            if(event.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}
