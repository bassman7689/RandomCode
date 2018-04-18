#include "headers.h"
#include "GameBall.h"

GameBall::GameBall()
{
    Load("images/ball.png");
    assert(IsLoaded());

    GetSprite().setPosition(GetSprite().getGlobalBounds().width/2 + 15,GetSprite().getGlobalBounds().height/2 + 15);
}

GameBall::~GameBall()
{
}
