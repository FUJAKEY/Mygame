#ifndef GRAPPLING_HOOK_H
#define GRAPPLING_HOOK_H

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Player;

class GrapplingHook {
public:
    GrapplingHook(b2World& world, Player* player);
    void fire(const b2Vec2& target);
    void release();
    bool isActive() const { return m_joint != nullptr; }
    void render(sf::RenderTarget& target);
private:
    b2World& m_world;
    Player* m_player;
    b2Body* m_anchor = nullptr;
    b2DistanceJoint* m_joint = nullptr;
    sf::VertexArray m_line;
};

#endif // GRAPPLING_HOOK_H
