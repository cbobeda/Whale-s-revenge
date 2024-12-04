#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace sf;
using namespace std;

int PosX = 0;
int PosY = 0;

void main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Whale-s-revenge");
    window.setFramerateLimit(60);

    sf::CircleShape shape(25);
    shape.setPosition(0,0);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOrigin(25, 25);

    vector<CircleShape> bulles;
    vector<float> angles;

    Clock clock;


    while (window.isOpen())
    {
        sf::Event event;

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            shape.move(5, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            shape.move(-5, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            shape.move(0, 5);
        }
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            shape.move(0, -5);
        }

        if (Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asSeconds() > 0.2) {
            bulles.push_back(CircleShape());
            bulles.back().setRadius(10);
            bulles.back().setOrigin(10, 10);
            bulles.back().setFillColor(Color::Blue);
            bulles.back().setPosition(shape.getPosition());
            angles.push_back(atan2(Mouse::getPosition(window).y - shape.getPosition().y, Mouse::getPosition(window).x - shape.getPosition().x));
            clock.restart();
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        for (int i = 0; i < bulles.size(); i++) {
            window.draw(bulles[i]);
            bulles[i].move(15 * cos(angles[i]), 15 * sin(angles[i]));
        }
        window.display();
        
    }
}