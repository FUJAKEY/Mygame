#include "GameContactListener.h"

void GameContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    void* ptrA = reinterpret_cast<void*>(bodyA->GetUserData().pointer);
    void* ptrB = reinterpret_cast<void*>(bodyB->GetUserData().pointer);

    if (ptrA == m_player) {
        if (auto* frozen = dynamic_cast<FrozenBlock*>(static_cast<Block*>(ptrB))) {
            float vy = -m_player->body()->GetLinearVelocity().y;
            frozen->onPlayerLand(m_player, vy);
        }
    } else if (ptrB == m_player) {
        if (auto* frozen = dynamic_cast<FrozenBlock*>(static_cast<Block*>(ptrA))) {
            float vy = -m_player->body()->GetLinearVelocity().y;
            frozen->onPlayerLand(m_player, vy);
        }
    }
}
