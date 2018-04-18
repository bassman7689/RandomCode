#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "TextureManager.h"
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "GameStateMachine.h"

class Game
{
public:
	~Game() {}

	bool init(const char *title, int xpos, int ypos, int height, int width, bool fullscreen);

	void render();
	void update();
	void handleEvents();
	void clean();
	static Game* Instance();

	// a function to access the private running variable
	bool running() { return m_bRunning; }

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	void quit() { m_bRunning = false; }

private:
	Game() {}
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;

    GameStateMachine* m_pGameStateMachine;
};

#endif /* defined(__Game__) */
