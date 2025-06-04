#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <box2d/box2d.h>
#include "FrozenBlock.h"

class Level {
public:
    explicit Level(b2World& world);
    void load(const std::string& filename);
    void update(float dt);
    void render(sf::RenderTarget& target);

private:
    b2World& m_world;
    std::vector<std::unique_ptr<Block>> m_blocks;
};

#endif // LEVEL_H
