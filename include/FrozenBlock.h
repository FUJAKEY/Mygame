#ifndef FROZEN_BLOCK_H
#define FROZEN_BLOCK_H

#include "Block.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class FrozenBlock : public Block {
public:
    FrozenBlock(b2World& world, const sf::Vector2f& position);
    void onPlayerLand(Player* p, float verticalSpeed) override;
    b2Body* body() { return m_body; }
    const sf::RectangleShape& shape() const { return m_shape; }

private:
    b2Body* m_body = nullptr;
    sf::RectangleShape m_shape;
};

#endif // FROZEN_BLOCK_H
