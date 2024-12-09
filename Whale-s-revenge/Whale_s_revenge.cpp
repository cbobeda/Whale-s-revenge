#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Main menu.h"
#include "Player.h"
#include "Ennemy.h"
#include <string>

using namespace sf;
using namespace std;

Player player;
Shark sharks;

bool createShark = false;
bool isDead = false;

Texture backgroundTexture;
Texture waveTexture;
IntRect whaleRect;
Clock watchanime;
float frameDurationanime = 0.1f; // Durée d'une frame (en secondes)
size_t currentFrameanime = 0;


void main()
{
    string MetalScrapString = to_string(player.MetalScrap);
    backgroundTexture.loadFromFile("sky.png");
    backgroundTexture.setRepeated(true);
    waveTexture.loadFromFile("vagues.png");
    Sprite skySprite;
    Sprite skySprite2;
    Sprite waveSprite;
    Sprite waveSprite2;
    Sprite whaleSprite;
    skySprite.setTexture(backgroundTexture);
    skySprite2.setTexture(backgroundTexture);
    waveSprite.setTexture(waveTexture);
    waveSprite2.setTexture(waveTexture);
    skySprite2.setPosition(backgroundTexture.getSize().x,0);
    waveSprite2.setPosition(waveTexture.getSize().x,0);
    whaleSprite.setTextureRect(whaleRect);
    srand(static_cast<unsigned int>(time(nullptr)));
    player.InitializePlayer();
    RenderWindow window(VideoMode::getDesktopMode(), "Whale-s-revenge",Style::Fullscreen);
    window.setFramerateLimit(60);

    Clock clock;
    Clock CDCompetence;
    Main_menu m(600,600);

    // J'affiche pour voir si ca fonctionne pour le moment
    Font font;
    font.loadFromFile("MinecraftStandard.otf");

    Text ArgentTemp(MetalScrapString,font,50);
    ArgentTemp.setPosition(50, 50);

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
                sharks.CreateShark(100, 10);
                createShark = true;
            }
        }
        if (watchanime.getElapsedTime().asSeconds() > frameDurationanime) {
            IntRect newRect = player.PlayerSprite.getTextureRect();
            newRect.left += 64;
            if (newRect.left >= 640) {newRect.left -= 640;}
            player.PlayerSprite.setTextureRect(newRect);
            watchanime.restart();
        }
        
#pragma region Tire Principale & Secondaire
        if (Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asSeconds() > 0.4) {
            player.CreateBulles();
            player.angles.push_back(atan2(Mouse::getPosition(window).y - player.PlayerSprite.getPosition().y, Mouse::getPosition(window).x - player.PlayerSprite.getPosition().x));
            clock.restart();
        }

        if (Mouse::isButtonPressed(Mouse::Right) && CDCompetence.getElapsedTime().asSeconds() > 2) {
            if (player.MetalScrap >= 50) {
                player.MetalScrap -= 50;
                player.CreateWave();
                player.angles.push_back(atan2(Mouse::getPosition(window).y - player.PlayerSprite.getPosition().y, Mouse::getPosition(window).x - player.PlayerSprite.getPosition().x));
                CDCompetence.restart();
            }
            
        }

        for (size_t i = 0; i < player.timers1.size(); i++) {
            if (player.timers1[i].getElapsedTime().asSeconds() > 2) {
                player.DeleteBulles();
            }
        }
        for (size_t i = 0; i < player.timers2.size(); i++) {
            if (player.timers2[i].getElapsedTime().asSeconds() > 2.5f) {
                player.DeleteWave();
            }
        }
#pragma endregion Tire Principale & Secondaire
        
        for (size_t i = 0; i < player.bulles.size(); ++i) {
            for (size_t j = 0; j < sharks.sharks.size(); ++j) {
                if (player.bulles[i].getGlobalBounds().intersects(sharks.sharks[j].shape.getGlobalBounds())) {
                    player.DeleteBulles();
                    sharks.takeDamage(j, player.PlayerDamage);
                    if (sharks.takeDamage(j, player.PlayerDamage)) {
                        player.MetalScrap += 10;
                    }
                    i--;
                    break;
                }
            }
        }

        for (size_t i = 0; i < player.wave.size(); ++i) {
            for (size_t j = 0; j < sharks.sharks.size(); ++j) {
                if (player.wave[i].getGlobalBounds().intersects(sharks.sharks[j].shape.getGlobalBounds())) {
                    sharks.takeDamage(j, player.PlayerDamage);
                    if (sharks.takeDamage(j, player.PlayerDamage)) {
                        player.MetalScrap += 10;
                    }
                    i--;
                    break;
                }
            }
        }

        for (size_t i = 0; i < sharks.ennemyATK.size(); i++) {
            if (sharks.ennemyATK[i].getGlobalBounds().intersects(player.PlayerSprite.getGlobalBounds())) {
                cerr << "DEGATS PRIT" << endl;
                sharks.DeleteATK();
                player.TakeDamage(); // A revoir plus tard
            }
        }

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (skySprite.getPosition().x + backgroundTexture.getSize().x < 0) {
            skySprite.setPosition(skySprite2.getPosition().x + backgroundTexture.getSize().x, 0);
        }
        if (waveSprite.getPosition().x + waveTexture.getSize().x < 0)
        {
            waveSprite.setPosition(waveSprite2.getPosition().x + waveTexture.getSize().x, 0);
        }
        if (skySprite2.getPosition().x + backgroundTexture.getSize().x < 0) {
            skySprite2.setPosition(skySprite.getPosition().x + backgroundTexture.getSize().x, 0);
        }
        if (waveSprite2.getPosition().x + waveTexture.getSize().x < 0)
        {
            waveSprite2.setPosition(waveSprite.getPosition().x + waveTexture.getSize().x, 0);
        }
        
        skySprite.move(- 5, 0);
        skySprite2.move(-5, 0);
        waveSprite.move(-10, 0);
        waveSprite2.move(-10, 0);
        whaleSprite.setPosition(whaleSprite.getPosition().x + 64, 0);
        window.clear();
        if (m.mdisplay(window))
        {
            
        }
        else
        {
            window.draw(skySprite);
            window.draw(skySprite2);
            window.draw(waveSprite);
            window.draw(waveSprite2);
            window.draw(player.PlayerSprite);

            for (int i = 0; i < player.bulles.size(); i++) {
                window.draw(player.bulles[i]);
                player.bulles[i].move(15 * cos(player.angles[i]), 15 * sin(player.angles[i]));
            }
            for (int i = 0; i < player.wave.size(); i++) {
                window.draw(player.wave[i]);
                player.wave[i].move(15 * cos(player.angles[i]), 15 * sin(player.angles[i]));
            }
        }
        

#pragma region Requins
        sharks.draw(window);

        if (sharks.SharkCreated) {
            sharks.moveAll();
        }
        for (int i = 0; i < sharks.ennemyATK.size(); i++) {
            window.draw(sharks.ennemyATK[i]);
            sharks.ennemyATK[i].move(-10, 0);
        }
#pragma endregion Requins

        string MetalScrapString = to_string(player.MetalScrap);
        ArgentTemp.setString(MetalScrapString);

        window.draw(ArgentTemp);
        window.display();
        
       /* if (!isDead) {
            if (player.Life <= 0) {
                isDead = true;
                m.actmenu();
                sharks.DeleteAll();
                player.MetalScrap = 0;
            }
        }*/
    }
}