#include "Game.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char *title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;

	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE) >= 0)
	{
		std::cout << "SDL init success" << std::endl;
	}
	else
       	{
		std::cout << "window init fail" << std::endl;
		return false;
	}
	
	// if succeeded create our window
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

	if(m_pWindow != 0)
	{
		std::cout << "window creation success" << std::endl;
	}
	else
	{
		std::cout << "window init fail" << std::endl;
		return false;
	}

	// if window creation succceded create our renderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	if(m_pRenderer != 0)
	{
		std::cout << "renderer creation success" << std::endl;
	}
	else
	{
		std::cout << "renderer creation fail" << std::endl;
		return false;
	}

	if(TextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
	{
		std::cout << "animate load success" << std::endl;
	}
	else
	{
		std::cout << "animate load fail" << std::endl;
		return false;
	}

	InputHandler::Instance()->initializeJoysticks();
	if(InputHandler::Instance()->joysticksInitialized())
	{
		std:: cout << "joysticks initialization success" << std::endl;
	}
	else
	{
		std::cout << "joysticks initialization fail" << std::endl;
	}

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());

	std::cout << "init success" << std::endl;
	m_bRunning = true;

	return true;
}

void Game::render()
{
	// clear the window to black
	SDL_RenderClear(m_pRenderer);

    m_pGameStateMachine->render();

	// show the window
	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
	InputHandler::Instance()->update();
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;
	InputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

Game* Game::Instance()
{
	if(s_pInstance == 0)
	{
		s_pInstance = new Game();
	}

	return s_pInstance;
}
