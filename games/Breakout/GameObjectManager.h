#ifndef __GAME_OBJECT_MANAGER__
#define __GAME_OBJECT_MANAGER__
#include "VisibleGameObject.h"

class GameObjectManager
{
public:
    GameObjectManager();
    ~GameObjectManager();

    void Add(std::string name, VisibleGameObject* gameObject);
    void Remove(std::string name);
    int GetObjectCount() const;
    VisibleGameObject* Get(std::string name) const;

    void DrawAll(sf::RenderWindow& window);
    void UpdateAll(float elapsedTime);

private:
    std::map<std::string, VisibleGameObject*> _gameObjects;

    struct GameObjectDeallocator
    {
        void operator()(const std::pair<std::string,VisibleGameObject*> &p) const
        {
            delete p.second;
        }
    };
};

#endif
