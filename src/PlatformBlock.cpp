#include "PlatformBlock.h"

PlatformBlock::PlatformBlock(b2World& world, const sf::Vector2f& position) {
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position.Set(position.x, position.y);
    m_body = world.CreateBody(&def);

    b2PolygonShape shape;
    shape.SetAsBox(0.5f, 0.5f);
    m_body->CreateFixture(&shape, 0.0f);
    m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    m_shape.setSize(sf::Vector2f(1.f, 1.f));
    m_shape.setFillColor(sf::Color(100, 100, 100));
    m_shape.setOrigin(0.5f, 0.5f);
    m_shape.setPosition(position);
}
