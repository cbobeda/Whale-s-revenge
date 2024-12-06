#include "button.h"


bool button::check(int x, int y, sf::RenderWindow& window) {
    sf::Vector2f worldCoords = window.mapPixelToCoords(sf::Vector2i(x, y)); // Conversion vue
    sf::IntRect buttonRect(posX, posY, width, height);
    return buttonRect.contains(static_cast<int>(worldCoords.x), static_cast<int>(worldCoords.y));
}

sf::RectangleShape button::bdisplay(sf::Color couleur, sf::Color couleur2) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(posX, posY);
    rectangle.setFillColor(couleur);
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(couleur2);

    return rectangle;
}
