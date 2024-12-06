#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Player.h"
#include "Ennemy.h"

using namespace sf;
using namespace std;

int BulleIndex = 0;

int PosX = 0;
int PosY = 0;
Player player;
Shark sharks;

bool createShark = false;

void main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    player.InitializePlayer();
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Whale-s-revenge",Style::Fullscreen);
    window.setFramerateLimit(60);

    RectangleShape Test(Vector2f(400, 200));
    Test.setFillColor(Color::Magenta);
    Test.setPosition(1500, 300);

    Clock clock;
    Clock TimerTest;

    while (window.isOpen())
    {
        sf::Event event;

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

        if (Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asSeconds() > player.ProjectileSpeed) {
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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
#pragma region Requins
        sharks.draw(window);

        if (sharks.SharkCreated) {
            window.draw(Test);
            Test.move(-5, 0);
            sharks.moveAll();
        }
#pragma endregion Requins
        window.draw(player.PlayerSprite);
        for (int i = 0; i < player.bulles.size(); i++) {
            window.draw(player.bulles[i]);
            player.bulles[i].move(15 * cos(player.angles[i]), 15 * sin(player.angles[i]));
        }
        window.display();
        
    }
}