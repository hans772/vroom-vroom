#include "Game.hpp"
#include "states/demo_state.hpp"
#include "render/render_context.hpp"
#include <SFML/Graphics.hpp>
#include "util/logger.hpp"

void Game::run() {

    GameStateManager::get().push(std::make_unique<DemoState>());
    GameStateManager::get().applyQueuedActions();

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "Vroom Vroom");
    window.setKeyRepeatEnabled(false);
    sf::Clock clock;


    while (!GameStateManager::get().empty()) {
        RenderContext ctx(window);

        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();


        GameStateManager::get().handleInput(window, dt);
        GameStateManager::get().update(dt);
        GameStateManager::get().render(ctx);

        window.display();
        GameStateManager::get().applyQueuedActions();
    }
}