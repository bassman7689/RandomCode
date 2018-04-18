#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"
#include "InputHandler.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);

	void draw();
	void update();
	void clean();
	
private:
	void handleInput();
};

#endif /* defined(__Player__) */
