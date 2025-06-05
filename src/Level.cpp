#include "Level.h"
#include "Player.h"
#include <fstream>

Level::Level(b2World& world) : m_world(world) {}

void Level::load(const std::string& filename) {
    std::ifstream in(filename);
    std::string line;
    int y = 0;
    while (std::getline(in, line)) {
        for (size_t x = 0; x < line.size(); ++x) {
            sf::Vector2f pos(static_cast<float>(x), static_cast<float>(y));
            switch (line[x]) {
            case '1':
                m_blocks.emplace_back(std::make_unique<PlatformBlock>(m_world, pos));
                break;
            case '3':
                m_blocks.emplace_back(std::make_unique<FrozenBlock>(m_world, pos));
                break;
            default:
                break;
            }
        }
        ++y;
    }
}

void Level::update(float dt) {
    // TODO update moving platforms
}

void Level::render(sf::RenderTarget& target) {
    for (auto& b : m_blocks) {
        if (auto* f = dynamic_cast<FrozenBlock*>(b.get())) {
            target.draw(f->shape());
        } else if (auto* p = dynamic_cast<PlatformBlock*>(b.get())) {
            target.draw(p->shape());
        }
    }
}
