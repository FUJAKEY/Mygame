#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game()
    : m_world(b2Vec2(0.0f, 9.8f)),
      m_player(m_world),
      m_level(m_world),
      m_listener(&m_player) {
    m_world.SetContactListener(&m_listener);
    m_level.load("assets/level.csv");
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "MyGame");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        m_player.handleInput(window);
        m_world.Step(1.f/60.f, 8, 3);
        m_player.update(1.f/60.f);
        m_level.update(1.f/60.f);
        window.clear();
        m_level.render(window);
        m_player.render(window);
        window.display();
    }
}
