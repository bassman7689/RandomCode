#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "PlayerPaddle.h"
#include "GameBall.h"

void Game::Start()
{
    if(_gameState != Uninitialized) {
        return;
    }

    _mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");

    PlayerPaddle *player1 = new PlayerPaddle();
    player1->Load("images/paddle.png");
    player1->SetPosition((1024/2)-45, 700);

    GameBall *ball = new GameBall();
    ball->SetPosition((SCREEN_WIDTH/2), (SCREEN_HEIGHT/2) - 15);

    _gameObjectManager.Add("Paddle1", player1);
    _gameObjectManager.Add("Ball", ball);

    _gameState = Game::ShowingSplash;

    while(!IsExiting())
    {
        GameLoop();
    }

    _mainWindow.close();
}

bool Game::IsExiting()
{
    return (_gameState == Game::Exiting);
}

void Game::GameLoop()
{
    sf::Event event;
    _mainWindow.pollEvent(event);

    switch(_gameState) {
        case Game::ShowingMenu:
            {
                ShowMenu();
                break;
            }
        case Game::ShowingSplash:
            {
                ShowSplashScreen();
                break;
            }
        case Game::Playing:
            {
                _mainWindow.clear(sf::Color(0, 0, 0));

                _gameObjectManager.UpdateAll(_clock.restart().asSeconds());
                _gameObjectManager.DrawAll(_mainWindow);

                _mainWindow.display();
                if(event.type == sf::Event::Closed)
                {
                    _gameState = Game::Exiting;
                }
                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Key::Escape)
                    {
                        ShowMenu();
                    }
                }
                break;
            }
        default:
            {
                break;
            }
    }


}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch(result)
    {
        case MainMenu::Exit:
            _gameState = Game::Exiting;
            break;
        case MainMenu::Play:
            _gameState = Game::Playing;
            break;
        case MainMenu::Nothing:
            break;
    }
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::Clock Game::_clock;
