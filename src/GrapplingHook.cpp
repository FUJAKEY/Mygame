#include "GrapplingHook.h"
#include "Player.h"

GrapplingHook::GrapplingHook(b2World& world, Player* player)
    : m_world(world), m_player(player), m_line(sf::Lines, 2) {}

void GrapplingHook::fire(const b2Vec2& target) {
    if (m_joint) return;
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position = target;
    m_anchor = m_world.CreateBody(&def);

    b2DistanceJointDef jd;
    jd.bodyA = m_player->body();
    jd.bodyB = m_anchor;
    jd.length = b2Distance(m_player->body()->GetPosition(), target);
    jd.collideConnected = true;
    m_joint = static_cast<b2DistanceJoint*>(m_world.CreateJoint(&jd));
}

void GrapplingHook::release() {
    if (m_joint) {
        m_world.DestroyJoint(m_joint);
        m_world.DestroyBody(m_anchor);
        m_joint = nullptr;
        m_anchor = nullptr;
    }
}

void GrapplingHook::render(sf::RenderTarget& target) {
    if (!m_joint) return;
    b2Vec2 a = m_player->body()->GetPosition();
    b2Vec2 b = m_anchor->GetPosition();
    m_line[0].position = sf::Vector2f(a.x, a.y);
    m_line[1].position = sf::Vector2f(b.x, b.y);
    target.draw(m_line);
}
