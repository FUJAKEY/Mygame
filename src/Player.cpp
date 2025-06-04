#include "Player.h"

Player::Player(b2World& world) {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    m_body = world.CreateBody(&def);

    b2PolygonShape box;
    box.SetAsBox(0.5f, 1.0f);
    m_body->CreateFixture(&box, 1.0f);

    // store pointer to this player in the body user data for contact callbacks
    m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Player::handleInput() {
    // stub
}

void Player::update(float dt) {
    if (m_frozen) {
        m_body->SetLinearVelocity(b2Vec2(0,0));
        m_body->SetGravityScale(0);
        return;
    }
}

void Player::render(sf::RenderTarget& target) {
    // stub
}

void Player::respawn() {
    m_frozen = false;
    m_body->SetTransform(b2Vec2(0,0), 0);
    m_body->SetGravityScale(1);
}

void Player::onFallOntoFrozenBlock() {
    m_frozen = true;
}
