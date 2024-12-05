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

void main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    player.InitializePlayer();
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Whale-s-revenge",Style::Fullscreen);
    window.setFramerateLimit(60);

    RectangleShape Shark(Vector2f(200, 75));
    Shark.setFillColor(Color::Red);
    Shark.setPosition(1800, 800);

    Clock clock;

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
            sharks.CreateShark();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.ProjectileSpeed += 0.05f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.ProjectileSpeed -= 0.05f;
        }

        if (!player.bulles.empty()) {
            if (player.bulles.back().getGlobalBounds().intersects(Shark.getGlobalBounds())) {
                player.DeleteBulles();
                BulleIndex += 1;
                if (BulleIndex == 4) {
                    Shark.setPosition(4000, 4000);
                    BulleIndex = 0;
                }
            }
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

        Vector2f playerPos = player.PlayerSprite.getPosition();
        Vector2f enemyPos = Shark.getPosition();
        Vector2f direction = playerPos - enemyPos;
       
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction /= length;
        }

        window.clear();
        window.draw(Shark);

        for(const auto&)

        if (Shark.getPosition().x - player.PlayerSprite.getPosition().x > 500 || Shark.getPosition().y - player.PlayerSprite.getPosition().y > 500) {
            Shark.move(direction * player.Speed);
        }
        

        window.draw(player.PlayerSprite);
        for (int i = 0; i < player.bulles.size(); i++) {
            window.draw(player.bulles[i]);
            player.bulles[i].move(15 * cos(player.angles[i]), 15 * sin(player.angles[i]));
        }
        window.display();
        
    }
}