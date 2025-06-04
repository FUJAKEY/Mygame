#ifndef GAME_CONTACT_LISTENER_H
#define GAME_CONTACT_LISTENER_H

#include <box2d/box2d.h>
#include "FrozenBlock.h"
#include "Player.h"

class GameContactListener : public b2ContactListener {
public:
    explicit GameContactListener(Player* p) : m_player(p) {}
    void BeginContact(b2Contact* contact) override;
private:
    Player* m_player;
};

#endif // GAME_CONTACT_LISTENER_H
