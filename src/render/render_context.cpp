#include "render/render_context.hpp"

RenderContext::RenderContext(sf::RenderWindow& window)
    : m_window(window) {
}

void RenderContext::clear() {
    m_window.clear();
}

void RenderContext::display() {
    m_window.display();
}

void RenderContext::draw(const sf::Drawable& drawable) {
    m_window.draw(drawable);
}

sf::RenderWindow& RenderContext::window() {
    return m_window;
}

sf::Vector2u RenderContext::getSize() {
    return m_window.getSize();
}