#ifndef __VISIBLE_GAME_OBJECT__
#define __VISIBLE_GAME_OBJECT__

#include "headers.h"

class VisibleGameObject
{
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();

    virtual void Load(std::string filename);
    virtual void Draw(sf::RenderWindow& window);
    virtual void Update(float elapsedTime);

    virtual void SetPosition(float x, float y);
    virtual sf::Vector2f GetPosition() const;
    virtual bool IsLoaded() const;

protected:
    sf::Sprite& GetSprite();

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    std::string _filename;
    bool _isLoaded;
};

#endif
