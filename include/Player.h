#ifndef PLAYER_H
#define PLAYER_H

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "GrapplingHook.h"

class Player {
public:
    Player(b2World& world);
    void handleInput(const sf::RenderWindow& window);
    void update(float dt);
    void render(sf::RenderTarget& target);
    void respawn();
    void onFallOntoFrozenBlock();
    bool isFrozen() const { return m_frozen; }
    b2Body* body() { return m_body; }

private:
    b2Body* m_body;
    sf::RectangleShape m_shape;
    bool m_frozen = false;
    GrapplingHook m_hook;
};

#endif // PLAYER_H
