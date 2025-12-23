#pragma once

#include "core/game_state.hpp"
#include <SFML/Graphics.hpp>
#include "core/gsm.hpp"

class DemoState : public GameState {
public:
    explicit DemoState();
    
    void update(float dt) override;
    void render(RenderContext& ctx) override;
    
    void changeColor();

private:
    sf::Color color;
};