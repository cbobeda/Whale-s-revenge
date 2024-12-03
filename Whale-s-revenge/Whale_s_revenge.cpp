#include <iostream>
#include <SFML/Graphics.hpp>

void main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Whale-s-revenge");
    window.setFramerateLimit(60);
    sf::CircleShape shape(50);
    shape.setPosition(0,0);
    shape.setFillColor(sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
        
    }
}