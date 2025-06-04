#include "Level.h"
#include "Player.h"

Level::Level(b2World& world) : m_world(world) {}

void Level::load(const std::string& filename) {
    (void)filename;
    // create a single frozen block as a placeholder
    m_blocks.emplace_back(std::make_unique<FrozenBlock>(m_world, sf::Vector2f(5.f, 10.f)));
}

void Level::update(float dt) {
    // TODO update moving platforms
}

void Level::render(sf::RenderTarget& target) {
    for (auto& b : m_blocks) {
        if (auto* f = dynamic_cast<FrozenBlock*>(b.get())) {
            target.draw(f->shape());
        }
    }
}
