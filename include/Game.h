#ifndef GAME_H
#define GAME_H

#include <box2d/box2d.h>
#include "Level.h"
#include "Player.h"
#include "GameContactListener.h"

class Game {
public:
    Game();
    void run();
private:
    b2World m_world;
    Player m_player;
    Level m_level;
    GameContactListener m_listener;
};

#endif // GAME_H
