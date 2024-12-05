#include "button.h"


bool button::check(int x, int y)
{
    
    if (x > posX && x < posX + width && y > posY && y < posY + height)
        return true;
    else
        return false;
}

sf::RectangleShape button::bdisplay(sf::Color couleur,sf::Color couleur2)
{
    sf::RectangleShape rectangle(sf::Vector2f(height, width));
    rectangle.setPosition(posX +5 , posY + 5);
    rectangle.setFillColor(couleur);
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(couleur2);
    
    return rectangle;
}