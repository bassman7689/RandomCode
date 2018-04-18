#ifndef __PLAYER_PADDLE__
#define __PLAYER_PADDLE__
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject
{
public:
    PlayerPaddle();
    ~PlayerPaddle();

    void Update(float elapsedTime);
    void Draw(sf::RenderWindow& window);

    float GetVelocity() const;

private:
    float _velocity;
    float _maxVelocity;
};

#endif
