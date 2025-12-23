#include "render/render_context.hpp"

RenderContext::RenderContext(sf::RenderWindow& window)
    : window(window) {
}

void RenderContext::clear() {
    window.clear();
}

void RenderContext::display() {
    window.display();
}

void RenderContext::draw(const sf::Drawable& drawable) {
    window.draw(drawable);
}

sf::RenderWindow& RenderContext::window() {
    return window;
}

sf::Vector2u RenderContext::getSize() {
    return window.getSize();
}