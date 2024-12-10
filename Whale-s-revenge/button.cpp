#include "button.h"


using namespace sf;
bool button::check(int x, int y, sf::RenderWindow& window) {
    sf::Vector2f worldCoords = window.mapPixelToCoords(sf::Vector2i(x, y)); // Conversion vue
    sf::IntRect buttonRect(posX, posY, width, height);
    return buttonRect.contains(static_cast<int>(worldCoords.x), static_cast<int>(worldCoords.y));
}

void button::setclicked(bool reset)
{
    if (clicked)
    {
        clicked = false;
    }
    else
    {
        clicked = true;
    }
    if (reset)
    {
        clicked = false;
    }
}


void button::bdisplay(sf::Color couleur, sf::Color couleur2,sf::RenderWindow& window,int size,sf::String isText) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(posX, posY);
    rectangle.setFillColor(couleur);
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(couleur2);
    if (tcheck)
    {
        if (clicked)
        {
            rectangle.setFillColor(Color(couleur.r/2, couleur.g/2, couleur.b/2));
        }
    }
    window.draw(rectangle);
    Text text;
    
    if (isText!="")
    {
        Font font;
        font.loadFromFile("MinecraftStandard.otf");
        text.setFont(font);
        text.setString(isText);
        text.setCharacterSize(size);
        text.setFillColor(Color::White);
        text.setOutlineColor(Color::Black);
        text.setOutlineThickness(3);
        sf::FloatRect textrect = text.getGlobalBounds();
        text.setOrigin(Vector2f(textrect.left + textrect.width/2,textrect.top + textrect.height/2));
        text.setPosition(Vector2f(posX + width/2,posY + height/2));
        text.setScale(1.5,1.5);
        window.draw(rectangle);
        window.draw(text);
    }
}
