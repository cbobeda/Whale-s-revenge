#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <cmath>
#include "Main menu.h"
#include "Player.h"
#include "Ennemy.h"
#include "bullet.h"
#include <string>
#include "SkillTree.h"

using namespace sf;
using namespace std;

Player player;
vector<Shark> sharksvect;
Shark sharks(sf::Vector2f(5, 5), sf::Vector2f(rand() % 2200 + 2000, rand() % 600 + 300), 0, false);

vector<Boat> boatvect;
Boat boat(sf::Vector2f(100, 50), sf::Color(38, 182, 122), sf::Vector2f(500, 300), 5, -8);
Boss boss;

MenuIndex menuindex;
SkillMenu sMenu;

bool createShark = false;
bool isDead = false;

Clock SkillMDelay;
int WaveIndex = 0;

//A supprimé plus tard
Clock NDelay;
bool BossCreated = false;
//
Texture backgroundTexture;
Texture waveTexture;
Texture requinTexture;
Texture hearTexture;
IntRect whaleRect;
Clock watchanime;
float frameDurationanime = 0.1f; // Durée d'une frame (en secondes)
size_t currentFrameanime = 0;

class Projectile {
public:
    float directionX, directionY;
    bool hasDirection = false;

    // Autres attributs et méthodes...
};

void main()
{
    string MetalScrapString = to_string(player.MetalScrap);
    backgroundTexture.loadFromFile("assets/sky.png");
    backgroundTexture.setRepeated(true);
    waveTexture.loadFromFile("assets/vagues.png");
    requinTexture.loadFromFile("assets/shark1.png");
    hearTexture.loadFromFile("assets/heartDisplay.png");
    Sprite skySprite;
    Sprite skySprite2;
    Sprite waveSprite;
    Sprite waveSprite2;
    Sprite waveBackgroundSprite;
    Sprite waveBackgroundSprite2;
    Sprite whaleSprite;
    Sprite heartSprite;
    skySprite.setTexture(backgroundTexture);
    skySprite2.setTexture(backgroundTexture);
    waveSprite.setTexture(waveTexture);
    waveSprite2.setTexture(waveTexture);
    heartSprite.setTexture(hearTexture);
    skySprite2.setPosition(backgroundTexture.getSize().x, 0);
    waveSprite2.setPosition(waveTexture.getSize().x, 0);
    whaleSprite.setTextureRect(whaleRect);
    srand(static_cast<unsigned int>(time(nullptr)));
    player.InitializePlayer();
    RenderWindow window(VideoMode::getDesktopMode(), "Whale-s-revenge", Style::Fullscreen);
    window.setFramerateLimit(60);

    Clock clock;
    Clock CDCompetence;
    Main_menu m(600, 600);

    Font font;
    font.loadFromFile("font/MinecraftStandard.otf");

    RectangleShape BlackBackground(Vector2f(2000, 2000));
    BlackBackground.setFillColor(Color::Black);
    BlackBackground.setPosition(0, 0);

    Text ArgentTemp(MetalScrapString, font, 50);
    ArgentTemp.setPosition(50, 50);

    while (window.isOpen())
    {
        Event event;



        if (Keyboard::isKeyPressed(Keyboard::D) && player.PlayerSprite.getPosition().x - player.Speed < 1800) {
            player.PlayerSprite.move(player.Speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q) && player.PlayerSprite.getPosition().x - player.Speed > 0) {
            player.PlayerSprite.move(-player.Speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Z) && player.PlayerSprite.getPosition().y - player.Speed > 400) {
            player.PlayerSprite.move(0, -player.Speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::S) && player.PlayerSprite.getPosition().y - player.Speed < 1000) {
            player.PlayerSprite.move(0, player.Speed);
        }

        if (Keyboard::isKeyPressed(Keyboard::P)) {
            if (!createShark) {
                sharks.CreateShark(2, 5, 5, 4);
                //boat.CreateBoats(1);
                createShark = true;
                WaveIndex++;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::B)) {
            boss.CreateSharkBoss();
        }

        if (Keyboard::isKeyPressed(Keyboard::N)) {
            if(NDelay.getElapsedTime().asSeconds() > 2){
                boss.SpecialBossATK();
                NDelay.restart();
                boss.isSpecialATK = true;
            }

        }

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.MetalScrap += 50;
        }

        if (watchanime.getElapsedTime().asSeconds() > frameDurationanime) {
            IntRect newRect = player.PlayerSprite.getTextureRect();
            newRect.left += 64;
            if (newRect.left >= 640) { newRect.left -= 640; }
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
            for (size_t j = 0; j < sharksvect.size(); ++j) {
                if (player.bulles[i].getGlobalBounds().intersects(sharksvect[j].rect.getGlobalBounds())) {
                    player.DeleteBulles();
                    sharksvect[j].takeDamage(j, player.PlayerDamage);
                    if (sharksvect[j].takeDamage(j, player.PlayerDamage)) {
                        player.MetalScrap += 10;
                    }
                    i--;
                    break;
                }
            }
        }

        for (size_t i = 0; i < player.wave.size(); ++i) {
            for (size_t j = 0; j < sharksvect.size(); ++j) {
                if (player.wave[i].getGlobalBounds().intersects(sharksvect[j].rect.getGlobalBounds())) {
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
            if (sharks.ennemyATK[i]->shape.getGlobalBounds().intersects(player.PlayerSprite.getGlobalBounds())) {
                sharks.DeleteATK(i);
                player.TakeDamage();
                break;
            }
        }

        for (size_t i = 0; i < sharksvect.size(); i++) {
            if (sharksvect[i].rect.getGlobalBounds().intersects(player.PlayerSprite.getGlobalBounds())) {
                player.TakeDamage();
                break;
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
        if (skySprite2.getPosition().x + backgroundTexture.getSize().x < 0)
        {
            skySprite2.setPosition(skySprite.getPosition().x + backgroundTexture.getSize().x, 0);
        }
        if (waveSprite2.getPosition().x + waveTexture.getSize().x < 0)
        {
            waveSprite2.setPosition(waveSprite.getPosition().x + waveTexture.getSize().x, 0);
        }

        skySprite.move(-5, 0);
        skySprite2.move(-5, 0);
        waveSprite.move(-10, 0);
        waveSprite2.move(-10, 0);
        waveBackgroundSprite.move(-10, 0);
        waveBackgroundSprite2.move(-10, 0);
        whaleSprite.setPosition(whaleSprite.getPosition().x + 64, 0);
        window.clear();
        if (m.mdisplay(window, event))
        {
            if (true)window.setPosition(sf::Vector2i(0 + rand() % 25, 0 + rand() % 25));
            sharks.SetDifficulty(m.DifficultyIndex);
            player.SetDifficulty(m.DifficultyIndex);
        }
        else
        {
            window.draw(skySprite);
            window.draw(skySprite2);
            window.draw(waveSprite);
            window.draw(waveSprite2);
            window.draw(waveBackgroundSprite);
            window.draw(waveBackgroundSprite2);
            window.draw(player.PlayerSprite);
            window.draw(boss.RequinBossShape);
            for (int i = 0; i < player.Life; i++)
            {
                heartSprite.setPosition(100 * i, 100);
                window.draw(heartSprite);
            }
            for (int i = 0; i < player.bulles.size(); i++) {
                window.draw(player.bulles[i]);
                player.bulles[i].move(20 * cos(player.angles[i]), 15 * sin(player.angles[i]));
            }
            for (int i = 0; i < player.wave.size(); i++) {
                window.draw(player.wave[i]);
                player.wave[i].move(20 * cos(player.angles[i]), 15 * sin(player.angles[i]));
            }
        }

        if (createShark) {
            if (sharksvect.size() == 0) {
                switch (WaveIndex) {
                case 1:
                    sharks.CreateShark(4, 6, 5, 4);
                    break;
                case 2:
                    sharks.CreateShark(9, 12, 5, 4);
                    break;
                case 3:
                    sharks.CreateShark(20, 15, 5, 4);
                    break;
                }
                WaveIndex++;
            }
        }



#pragma region Requins
        for (auto& shark : sharksvect)
        {
            shark.shape.setTexture(requinTexture);
            shark.rect.setPosition(shark.shape.getPosition().x, shark.shape.getPosition().y);
            window.draw(shark.shape);
        }

        for (auto& boats : boatvect) {
            window.draw(boats.boatshape);
        }

        if (sharksvect.size() != 0) {
            sharks.moveAll(player.PlayerSprite.getPosition());
            boat.MoveBoat();
        }

        for (int i = 0; i < sharks.ennemyATK.size(); i++) {
            window.draw(sharks.ennemyATK[i]->shape);
            sharks.ennemyATK[i]->update(sharks.ProjectileSpeed);
        }
        if (boatvect.size() > 0) {
            boat.BoatATK();
        }

        for (int i = 0; i < boat.boatATK.size(); i++) {
            window.draw(boat.boatATK[i]);
            if (boat.boatATK[i].getPosition().y <= 1000) {
                boat.boatATK[i].move(0, 5);
            }
            else if (boat.boatATK[i].getPosition().y >= 1000) {
                boat.BiggerATK(i);
            }
        }
#pragma endregion Requins

        string MetalScrapString = to_string(player.MetalScrap);
        ArgentTemp.setString(MetalScrapString);

        if (WaveIndex >= 0) {
            if (Keyboard::isKeyPressed(Keyboard::U)) {
                if (SkillMDelay.getElapsedTime().asSeconds() > 2) {
                    sMenu.switchUpgrading();
                    SkillMDelay.restart();
                }

            }
        }

        if (sMenu.isUpgrading) {
            window.draw(BlackBackground);
            sMenu.DisplaySkillMenu(window);
        }

        window.draw(ArgentTemp);

        window.display();
        if (m.isPlayingCustom) {
            if (sharksvect.size() <= 0 && boatvect.size() <= 0) {
                m.isPlayingCustom = false;
                m.actmenu();
            }
        }
        if (boss.isSpecialATK) {
            boss.SpecialBossATKMove();
        }
        else {
            boss.SpecialBossBackward();
        }
            

        if (!isDead) {
            if (player.Life <= 0) {
                isDead = true;
                m.actmenu();
                sharks.DeleteAll();
                player.MetalScrap = 0;
            }
        }
    }
}