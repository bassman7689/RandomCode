#ifndef __InputHandler__
#define __InputHandler__

#include <iostream>
#include <vector>
#include <utility>

#include <SDL2/SDL.h>

#include "Vector2D.h"

enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	void update();
	void clean();

	void initializeJoysticks();
	bool joysticksInitialized() { return m_bJoysticksInitialized; }

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	bool getButtonState(int joy, int buttonNumber);
	bool getMouseButtonState(int buttonNumber);
    void reset();

	bool isKeyDown(SDL_Scancode key);
	Vector2D* getMousePosition();

private:
	InputHandler();
	~InputHandler() {}

	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// handle joystick events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	static InputHandler* s_pInstance;

	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialized;
	std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;
	const int m_joystickDeadZone = 10000;

	std::vector<std::vector<bool> > m_buttonStates;

	Vector2D* m_mousePosition;
	std::vector<bool> m_mouseButtonStates;

	const Uint8* m_keystates;
};

#endif /* defined(__InputHandler__) */
