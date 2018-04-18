#ifndef __GAME__
#define __GAME__

#include "headers.h"
#include "GameObjectManager.h"

class Game
{
public:
    static void Start();
    const static int SCREEN_WIDTH = 1024;
    const static int SCREEN_HEIGHT = 768;

private:
    static bool IsExiting();
    static void GameLoop();

    static void ShowSplashScreen();
    static void ShowMenu();
    
    enum GameState {
        Uninitialized,
        ShowingSplash,
        Paused,
        ShowingMenu,
        Playing,
        Exiting
    };

    static GameState _gameState;
    static sf::RenderWindow _mainWindow;

    static GameObjectManager _gameObjectManager;

    static sf::Clock _clock;
};

#endif
