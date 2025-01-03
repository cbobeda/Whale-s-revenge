#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <math.h>
#include <cmath>
#include "Main menu.h"
#include "Player.h"
#include "Ennemy.h"
#include "bullet.h"
#include <string>
#include "SkillTree.h"
#include "bonus.h"
#include "fish.h"
#include "button.h"
#include "WaterPollution.h"

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

Pollution pollution;

extern button selectmenu_button;

bool createShark = false;
bool isDead = false;

Clock SkillMDelay;

int WaveIndex = 1;
int LevelIndex = 1;
button PlayWave(1780, 950, 100, 100, false);

//A supprimé plus tard
Clock NDelay;
//
Texture backgroundTexture;
Texture waveTexture;
Texture requinTexture;
Texture hearTexture;
IntRect whaleRect;
Clock watchanime;
float frameDurationanime = 0.1f; // Durée d'une frame (en secondes)
size_t currentFrameanime = 0;
bonus b(2000,500,10,10);
fish fish;

Music music;
SoundBuffer endofwave;
class Projectile {
public:
    float directionX, directionY;
    bool hasDirection = false;

    // Autres attributs et méthodes...
};

void main()
{
    string MetalScrapString = to_string(player.MetalScrap);
    string PollutionEauString = to_string(pollution.pollustate);
    backgroundTexture.loadFromFile("assets/sky.png");
    backgroundTexture.setRepeated(true);
    waveTexture.loadFromFile("assets/vagues.png");
    requinTexture.loadFromFile("assets/shark1.png");
    hearTexture.loadFromFile("assets/heartDisplay.png");
    Sprite skySprite;
    Sprite skySprite2;
    Sprite waveSprite;
    Sprite waveSprite2;
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
    srand(time(NULL));
    player.InitializePlayer();
    endofwave.loadFromFile("assets/endOfWave.wav");
    Sound endwave;
    endwave.setBuffer(endofwave);
    if (!music.openFromFile("assets/maintheme.ogg"))
        cout << "ne peut pas chargé la musique"; // erreur
    music.play();
    music.setLoop(true);
    RenderWindow window(VideoMode::getDesktopMode(), "Whale-s-revenge",Style::None);
    window.setFramerateLimit(60);

    Clock clock;
    Clock CDCompetence;
    Main_menu m(600, 600);

    Font font;
    font.loadFromFile("font/MinecraftStandard.otf");

    Text ArgentTemp(MetalScrapString, font, 50);
    ArgentTemp.setPosition(100, 100);

    Text PollutionEau(PollutionEauString, font, 50);
    PollutionEau.setPosition(1500, 50);

    while (window.isOpen())
    {
        Event event;
        

        if (Keyboard::isKeyPressed(Keyboard::D) && player.PlayerSprite.getPosition().x - player.Speed < 1800) {
            player.PlayerSprite.move(player.Speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q) && player.PlayerSprite.getPosition().x - player.Speed > 0) {
            player.PlayerSprite.move(-player.Speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Z) && player.PlayerSprite.getPosition().y - player.Speed > 470) {
            player.PlayerSprite.move(0, -player.Speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::S) && player.PlayerSprite.getPosition().y - player.Speed < 1000) {
            player.PlayerSprite.move(0, player.Speed);
        }

        if (Keyboard::isKeyPressed(Keyboard::O)) {
            menuindex = GameOver;
        }

        if (Keyboard::isKeyPressed(Keyboard::N)) {
            if (NDelay.getElapsedTime().asSeconds() > 2) {
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

        if (Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asSeconds() > player.ProjectileCD) {
            player.CreateBulles();
            player.angles.push_back(atan2(Mouse::getPosition(window).y - player.PlayerSprite.getPosition().y, Mouse::getPosition(window).x - player.PlayerSprite.getPosition().x));
            clock.restart();
        }

        if (Mouse::isButtonPressed(Mouse::Right) && CDCompetence.getElapsedTime().asSeconds() > player.SecondaryProjectileCD && player.CanSecondary) {
            if (player.MetalScrap >= 50) {
                player.MetalScrap -= 50;
                player.CreateWave();
                player.angles.push_back(atan2(Mouse::getPosition(window).y - player.PlayerSprite.getPosition().y, Mouse::getPosition(window).x - player.PlayerSprite.getPosition().x));
                CDCompetence.restart();
            }
        }
#pragma region Toutes les colisions
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
        /*for (size_t i = 0; i < player.timers3.size(); i++) {
            if (player.timers3[i].getElapsedTime().asSeconds() > 0.2) {
                player.DeleteExplosion();
            }
        }*/

        for (size_t i = 0; i < player.bulles.size(); ++i) {
            if (player.bulles[i].getGlobalBounds().intersects(boss.RequinBossShape.getGlobalBounds())) {
                player.DeleteBulles();
                boss.BossTakeDamage(player.PlayerDamage, m.DifficultyIndex);
            }
            for (size_t j = 0; j < sharksvect.size(); ++j) {
                if (player.bulles[i].getGlobalBounds().intersects(sharksvect[j].rect.getGlobalBounds())) {
                    player.DeleteBulles();
                    sharksvect[j].takeDamage(j, player.PlayerDamage); 
                        player.MetalScrap += 5;
                    
                    i--;
                    break;
                }
            }

            for (size_t o = 0; o < boss.Shields.size(); ++o) {
                if (player.bulles[i].getGlobalBounds().intersects(boss.Shields[o].getGlobalBounds())) {
                    player.DeleteBulles();
                    boss.SecondayBossTakeDamage(o);
                    i--;
                    break;
                }
            }
            for (size_t p = 0; p < boatvect.size(); p++) {
                if (player.bulles[i].getGlobalBounds().intersects(boatvect[p].boatshape.getGlobalBounds())) {
                    player.DeleteBulles();
                    if (boatvect[p].BoatLife <= 0) {
                        boat.DestroyBoat(p);
                    }
                    else {
                        boatvect[p].BoatTakeDamage(player.PlayerDamage);
                    }                   
                }
            }
        }

        for (size_t i = 0; i < player.wave.size(); ++i) {
            for (size_t o = 0; o < sharks.ennemyATK.size(); o++) {
                if (player.wave[i].getGlobalBounds().intersects(sharks.ennemyATK[o]->shape.getGlobalBounds())) {
                    sharks.DeleteATK(o);
                    break;
                }
            }
            for (size_t j = 0; j < sharksvect.size(); ++j) {
                if (player.wave[i].getGlobalBounds().intersects(sharksvect[j].rect.getGlobalBounds())) {
                    if (!player.SecondaryTechno) {
                        sharks.takeDamage(j, player.PlayerDamage); 
                            player.MetalScrap += 5;                       
                        i--;
                        break;
                    }
                    else {
                        //player.Explode();
                    }
                }
                    
            }
        }

        /*for (size_t i = 0; i < player.Explosion.size(); i++) {
            for (size_t j = 0; j < sharksvect.size(); ++j) {
                if (player.Explosion[i].getGlobalBounds().intersects(sharksvect[j].rect.getGlobalBounds())) {

                }
            }
        }*/

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
            if (sharksvect[i].rect.getPosition().x < 0) {
                sharks.DeleteShark(i);
            }
        }

        if (boss.RequinBossShape.getGlobalBounds().intersects(player.PlayerSprite.getGlobalBounds())) {
            player.TakeDamage();
        }

        for (size_t i = 0; i < boss.Shields.size(); i++) {
            if (boss.Shields[i].getGlobalBounds().intersects(player.PlayerSprite.getGlobalBounds())) {
                boss.SecondaryBossDestroy(i);
                player.TakeDamage();
            }
        }

        for (size_t i = 0; i < boss.SharkBossBulle.size(); i++) {
            if (boss.SharkBossBulle[i]->shape.getGlobalBounds().intersects(player.PlayerSprite.getGlobalBounds())) {
                boss.PrimaryATKDelete(i);
                player.TakeDamage();
            }
            if (boss.SharkBossBulle[i]->shape.getPosition().x < 0) {
                boss.PrimaryATKDelete(i);
            }
        }
#pragma endregion Toutes les colisions

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
        whaleSprite.setPosition(whaleSprite.getPosition().x + 64, 0);
        window.clear();
        if (m.mdisplay(window, event))
        {
            //if (true)window.setPosition(sf::Vector2i(0 + rand() % 25, 0 + rand() % 25));
            sharks.SetDifficulty(m.DifficultyIndex);
            player.SetDifficulty(m.DifficultyIndex);
        }
        else
        {
            fish.fishupdate();
            b.checkCollision(player);
            window.draw(skySprite);
            window.draw(skySprite2);
            for (auto& boats : boatvect) {
                window.draw(boats.boatshape);
            }
            window.draw(waveSprite);
            window.draw(waveSprite2);
            for (auto& shark : sharksvect)
            {
                shark.shape.setTexture(requinTexture);
                shark.rect.setPosition(shark.shape.getPosition().x, shark.shape.getPosition().y);
                window.draw(shark.shape);
            }
            window.draw(b.rect);
            window.draw(fish.sprite);
            window.draw(boss.RequinBossShape);
            if (!createShark && boss.life <= 0) {
                PlayWave.bdisplay(Color::Green, Color::Black, window, 20, ">");
            }
            if (PlayWave.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left)) {
                if (sharksvect.size() == 0 && boss.life <= 0) {
                    pollution.CanChange = true;
                    createShark = true;
                    switch (LevelIndex) {
                        case 1:
                            switch (WaveIndex) {
                            case 1:
                                endwave.play();
                                sharks.CreateShark(3, 4, 5, 4);
                                boat.CreateBoats(1);
                                break;
                            case 2:
                                endwave.play();
                                sharks.CreateShark(4, 6, 5, 4);
                                break;
                            case 3:
                                endwave.play();
                                sharks.CreateShark(6, 8, 5, 4);
                                break;
                            case 4:
                                endwave.play();
                                sharks.CreateShark(8, 10, 5, 4);
                                boat.CreateBoats(1);
                                break;
                            case 5:
                                endwave.play();
                                boss.CreateSharkBoss();
                                boss.BossCreated = true;
                                LevelIndex++;
                                WaveIndex = 0;
                                break;
                            }
                            WaveIndex++;
                            break;
                        case 2:
                            switch (WaveIndex) {
                            case 1:
                                endwave.play();
                                sharks.CreateShark(10, 10, 7, 6);
                                break;
                            case 2:
                                endwave.play();
                                sharks.CreateShark(30, 0, 8, 6);
                                break;
                            case 3:
                                endwave.play();
                                sharks.CreateShark(0, 20, 7, 5);
                                break;
                            case 4:
                                endwave.play();
                                sharks.CreateShark(15, 15, 7, 6);
                                break;
                            case 5:
                                //Boss 2
                                break;
                            }
                            WaveIndex++;
                            break;
                    }
                }                    
            }


            for (auto& shield : boss.Shields) {
                window.draw(shield);
            }

            if (!createShark) {
                if (Keyboard::isKeyPressed(Keyboard::U)) {
                    if (SkillMDelay.getElapsedTime().asSeconds() > 1.5) {
                        sMenu.switchUpgrading();
                        SkillMDelay.restart();
                    }
                }
            }

            if (pollution.PollutionClock.getElapsedTime().asSeconds() > 0.5) {
                if (!pollution.isPolluting) {
                    pollution.DecreasePollution();
                    pollution.PollutionClock.restart();
                }
                else {
                    pollution.IncreasePollution(m.DifficultyIndex);
                    pollution.PollutionClock.restart();
                }                
            }
            if (player.InvicibleFrame.getElapsedTime().asSeconds() < 1 && player.InvicibleFramShow.getElapsedTime().asSeconds() > 0.1) {
                player.ChangeShowValue();
                player.InvicibleFramShow.restart();
            }
            else {
                if (player.ShowPlayer) {
                    window.draw(player.PlayerSprite);
                }
                
            }

            if (player.InvicibleFrame.getElapsedTime().asSeconds() > 1) {
                player.ShowPlayer = true;
            }
            
            window.draw(ArgentTemp);
            window.draw(PollutionEau);

            for (int i = 0; i < player.Life; i++)
            {
                heartSprite.setPosition(65 * i, 0);
                window.draw(heartSprite);
            }
            for (int i = 0; i < player.bulles.size(); i++) {
                window.draw(player.bulles[i]);
                player.bulles[i].move(player.ProjectileSpeed * cos(player.angles[i]), player.ProjectileSpeed * sin(player.angles[i]));
            }
            for (int i = 0; i < player.wave.size(); i++) {
                window.draw(player.wave[i]);
                player.wave[i].move(player.SecondaryProjectileSpeed * cos(player.angles[i]), player.SecondaryProjectileSpeed* sin(player.angles[i]));
            }
            for (int i = 0; i < player.Explosion.size(); i++) {
                window.draw(player.Explosion[i]);
            }

            if (createShark) {
                if (sharksvect.size() == 0) {
                    createShark = false;
                    pollution.CanChange = false;
                }
            }

                if (boss.BossCreated) {
                    boss.MoveBoss();
                    boss.RequinBossShape.setTexture(boss.Bossrequin_texture);
                    int BossATK = (rand() % 11);
                    if (boss.SharkBossCD.getElapsedTime().asSeconds() > boss.ATKCD) {
                        boss.SharkBossCD.restart();
                        if (BossATK >= 0 && BossATK <= 3) {
                            boss.BasicBossATK(player.PlayerSprite.getPosition());
                        }
                        if (BossATK > 3 && BossATK <= 7) {
                            boss.SecondaryBossATK();
                        }
                        if (BossATK > 7 && BossATK <= 11) {
                            boss.isSpecialATK = true;
                        }
                    }
                }
                for (auto& shield : boss.Shields) {
                    shield.move(-9, 0);
            }
                if (boss.isSpecialATK) {
                    boss.SpecialBossATKMove();
                }
                else {
                    boss.SpecialBossBackward(window);
                }
                if (sharksvect.size() != 0) {
                    sharks.moveAll(player.PlayerSprite.getPosition());
                    boat.MoveBoat();
                }

                for (int i = 0; i < sharks.ennemyATK.size(); i++) {
                    window.draw(sharks.ennemyATK[i]->shape);
                    sharks.ennemyATK[i]->update(sharks.ProjectileSpeed);
                }

                for (int i = 0; i < boss.SharkBossBulle.size(); i++) {
                    window.draw(boss.SharkBossBulle[i]->shape);
                    boss.SharkBossBulle[i]->update(30);
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
                    for (auto& bulle : player.bulles)
                    {
                        if (boat.boatATK[i].getGlobalBounds().intersects(bulle.getGlobalBounds()))
                        {
                            pollution.isPolluting = false;
                            boat.boatATK.erase(boat.boatATK.begin() + i);
                        }
                    }
                }
        }

        string MetalScrapString = to_string(player.MetalScrap);
        ArgentTemp.setString(MetalScrapString);

        string PollutionEauString = to_string(pollution.pollustate);
        PollutionEau.setString(PollutionEauString);
       
        if (m.isPlayingCustom && sharksvect.size() <= 0 && boss.life <= 0) {
            if (m.isPlayingBoss1 && !boss.BossCreated) {
                boss.CreateSharkBoss();
                boss.BossCreated = true;
            }
            else {
                m.isPlayingCustom = false;
                m.actmenu();
            }
            if (boss.BossCreated && boss.life <= 0) {
                boss.BossCreated = false;
                m.isPlayingCustom = false;
                m.actmenu();
            }
        }

        if (sMenu.isUpgrading) {
            sMenu.DisplaySkillMenu(window);
        }

        if (!isDead) {
            if (player.Life <= 0 || pollution.pollustate >= 100) {
                isDead = true;
                pollution.pollustate = 0;
                pollution.CanChange = false;
                if (menuindex == Campagne)
                {
                    menuindex = GameOver;
                }
                m.actmenu();
                isDead = false;
                sharks.DeleteAll();
                player.MetalScrap = 0;
            }
        }
        window.display();        
    }
}