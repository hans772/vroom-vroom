#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

class RenderContext {
public:
    explicit RenderContext(sf::RenderWindow& window);

    void clear();
    void display();

    void draw(const sf::Drawable& drawable);

    sf::Vector2u getSize();
    sf::RenderWindow& window();

private:
    sf::RenderWindow& window;
};
