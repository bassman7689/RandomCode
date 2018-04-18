#ifndef __SCENE__
#define __SCENE__

#include "Menu.h"

class Scene {
public:
    Scene(Menu actionsMenu);
    ~Scene();

    void run();

private:
    Menu m_actionsMenu;
};

#endif
