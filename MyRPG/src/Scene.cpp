#include "Scene.h"

Scene::Scene(Menu actionsMenu) : m_actionsMenu(actionsMenu) { }
Scene::~Scene() {}

void Scene::run() {
    std::string selectedAction = m_actionsMenu.choose();

    std::cout << "You decided to " << selectedAction << std::endl;
}
