#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Main menu.h"
#include "Player.h"
#include "Ennemy.h"

Player player;
Shark sharks;

bool createShark = false;


using namespace sf;
using namespace std;
bool isMainMenu = true;
void main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    player.InitializePlayer();
    RenderWindow window(sf::VideoMode::getDesktopMode(), "Whale-s-revenge");
    window.setFramerateLimit(60);

    Clock clock;
    Main_menu m(600,600);

    while (window.isOpen())
    {
        Event event;

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.PlayerSprite.move(player.Speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            player.PlayerSprite.move(-player.Speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Z) && player.PlayerSprite.getPosition().y - player.Speed > 400) {
            player.PlayerSprite.move(0, -player.Speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.PlayerSprite.move(0, player.Speed);
        }

        if (Keyboard::isKeyPressed(Keyboard::P)) {
            if (!createShark) {
                sharks.CreateShark(5, 9);
                createShark = true;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.ProjectileSpeed += 0.05f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.ProjectileSpeed -= 0.05f;
        }

        if (Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asSeconds() > 0.2) {
            player.CreateBulles();
            player.angles.push_back(atan2(Mouse::getPosition(window).y - player.PlayerSprite.getPosition().y, Mouse::getPosition(window).x - player.PlayerSprite.getPosition().x));
            clock.restart();
        }

        for (size_t i = 0; i < player.timers.size(); i++) {
            if (player.timers[i].getElapsedTime().asSeconds() > 1) {
                player.DeleteBulles();
            }
        }

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        if (m.mdisplay(window))
        {
            
        }
        else
        {
            window.draw(player.PlayerSprite);
            for (int i = 0; i < player.bulles.size(); i++) {
                window.draw(player.bulles[i]);
                player.bulles[i].move(15 * cos(player.angles[i]), 15 * sin(player.angles[i]));
            }
        }

#pragma region Requins
        sharks.draw(window);

        if (sharks.SharkCreated) {
            sharks.moveAll();
        }
#pragma endregion Requins
        window.display();
        
    }
}