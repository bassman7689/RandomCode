#include "Game.h"

bool g_bRunning = false; // this will create a loop

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

Game * g_game = 0;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char *argv[])
{
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
	Uint32 frameStart, frameTime;

	std::cout << "Game init attempt..." << std::endl;

	if(!Game::Instance()->init("Chapter 1", 100, 100, 640, 480, false))
	{
		std::cout << "game init failure - " << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "game init success!" << std::endl;
	while(Game::Instance()->running())
	{
		frameStart = SDL_GetTicks();

		Game::Instance()->handleEvents();
		Game::Instance()->update();
		Game::Instance()->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

	Game::Instance()->clean();

	return 0;
}
