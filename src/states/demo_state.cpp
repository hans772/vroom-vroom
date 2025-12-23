#include "states/demo_state.hpp"
#include "core/gsm.hpp"

DemoState::DemoState() {

    ev_h.registerKeyEvent(sf::Keyboard::Scancode::B, std::bind(&DemoState::changeColor, this), false);
    color = sf::Color::White;
}

void DemoState::changeColor() {
    if (color == sf::Color::White) color = sf::Color::Black;
    else color = sf::Color::White;
}

void DemoState::update(float dt) {

}

void DemoState::render(RenderContext& ctx) {
    sf::RectangleShape rect = sf::RectangleShape( sf::Vector2f(ctx.getSize()));
    rect.setFillColor(color);

    ctx.draw(rect);
}