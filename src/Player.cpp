#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Player::Player(b2World& world)
    : m_hook(world, this) {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    m_body = world.CreateBody(&def);

    b2PolygonShape box;
    box.SetAsBox(0.5f, 1.0f);
    m_body->CreateFixture(&box, 1.0f);

    // store pointer to this player in the body user data for contact callbacks
    m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Player::handleInput(const sf::RenderWindow& window) {
    if (m_frozen) return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        m_hook.fire(b2Vec2(static_cast<float>(mouse.x)/50.f,
                           static_cast<float>(mouse.y)/50.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        m_hook.release();
    }
}

void Player::update(float dt) {
    if (m_frozen) {
        m_body->SetLinearVelocity(b2Vec2(0,0));
        m_body->SetGravityScale(0);
        return;
    }
}

void Player::render(sf::RenderTarget& target) {
    m_hook.render(target);
}

void Player::respawn() {
    m_frozen = false;
    m_body->SetTransform(b2Vec2(0,0), 0);
    m_body->SetGravityScale(1);
}

void Player::onFallOntoFrozenBlock() {
    m_frozen = true;
}
