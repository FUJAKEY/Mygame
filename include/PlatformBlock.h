#ifndef PLATFORM_BLOCK_H
#define PLATFORM_BLOCK_H

#include "Block.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class PlatformBlock : public Block {
public:
    PlatformBlock(b2World& world, const sf::Vector2f& position);
    b2Body* body() { return m_body; }
    const sf::RectangleShape& shape() const { return m_shape; }
private:
    b2Body* m_body = nullptr;
    sf::RectangleShape m_shape;
};

#endif // PLATFORM_BLOCK_H
