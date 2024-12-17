#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Ennemy.h"
#include <cstdlib>

using namespace sf;
#pragma region ClassRequin
extern std::vector<Shark> sharksvect;

void Shark::SetDifficulty(int DifficultyIndex) {
    switch (DifficultyIndex) {
    case 1:
        ProjectileSpeed = 15;
        break;
    case 2:
        ProjectileSpeed = 20;
        break;
    case 3:
        ProjectileSpeed = 80;
        break;
    }
}

void Shark::CreateShark(int MeleeSharks, int DistanceSharks, int MLife, int DLife) {
    int meleeLife = MLife;
    int distanceLife = DLife;

    for (int i = 0; i < MeleeSharks; i++) {
        sharksvect.emplace_back(sf::Vector2f(5, 5), sf::Vector2f(rand() % 2200 + 2000, rand() % 400 + 480), meleeLife, false);
    }

    for (int j = 0; j < DistanceSharks; j++) {
        sharksvect.emplace_back(sf::Vector2f(5, 5), sf::Vector2f(rand() % 2500 + 2000, rand() % 400 + 480), distanceLife, true);

    }
}

void Shark::moveAll(Vector2f playerpos) {
    for (auto& shark : sharksvect) {
        if (!shark.isRanged) {
            shark.shape.move(Speed, 0);
        }
        else {
            if (shark.shape.getPosition().x > 1700) {
                shark.shape.move(Speed, 0);
            }
            else {
                if (EnnemyATKCD.getElapsedTime().asSeconds() > 1) {
                    SharkATK(playerpos);
                    EnnemyATKCD.restart();
                }
            }
        }
    }
}

bool Shark::takeDamage(size_t sharkIndex, int damage) {
    if (sharkIndex < sharksvect.size()) {
        sharksvect[sharkIndex].life -= damage;

        if (sharksvect[sharkIndex].life <= 0) {
            sharksvect.erase(sharksvect.begin() + sharkIndex);
            return true;
        }
    }
    return false;
}

void Shark::SharkATK(Vector2f playerpos) {
    for (int i = 0; i < sharksvect.size(); i++) {
        if (sharksvect[i].isRanged) {
            ennemyATK.push_back(new bullet(playerpos, sharksvect[i].shape.getPosition()));
            for (auto& projectile : ennemyATK)
            {
                if (projectile->shape.getPosition().x == 0 && projectile->shape.getPosition().y == 0)
                {
                    projectile->init(sharksvect[i].shape.getPosition().x, sharksvect[i].shape.getPosition().y);
                }
            }
        }
    }
}

void Shark::DeleteShark(size_t sharkindex) {
    sharksvect.erase(sharksvect.begin() + sharkindex);
}

void Shark::DeleteAll() {
    sharksvect.clear();
    ennemyATK.clear();
}

void Shark::DeleteATK(size_t index) {
    ennemyATK.erase(ennemyATK.begin() + index);
}

#pragma endregion ClassRequin

#pragma region ClassBateau
extern std::vector<Boat> boatvect;

void Boat::CreateBoats(int BoatNumber) {
    int BaseBoatSpawn = 1500;
    for (int i = 0; i < BoatNumber; i++) {
        BaseBoatSpawn += (rand() % 900) + 1000;

        boatvect.emplace_back(sf::Vector2f(100, 50), sf::Color(38, 182, 122), sf::Vector2f(BaseBoatSpawn, 325), 5, Speed);
    }
}

void Boat::MoveBoat() {
    for (auto& boat : boatvect) {
        boat.boatshape.move(Speed, 0);
    }
}

void Boat::BoatATK() {
    for (auto& boat : boatvect) {
        if (!boat.hasAttacked && boat.boatshape.getPosition().x < 1900 && boat.boatshape.getPosition().x > 0) {
            if (boat.attackTimer.getElapsedTime().asMilliseconds() >= boat.attackDelay) {
                boatATK.push_back(sf::CircleShape());
                boatATK.back().setFillColor(sf::Color(161, 229, 54));
                boatATK.back().setPosition(boat.boatshape.getPosition());
                boatATK.back().setRadius(ATKRadius);
                boatATK.back().setOrigin(ATKRadius, ATKRadius);

                boat.hasAttacked = true;
            }
        }
    }
}

void Boat::BiggerATK(size_t index) {
    if (index < boatATK.size() && BiggerATKCD.getElapsedTime().asSeconds() > 0.5) {
        ATKRadius += 5;
        boatATK[index].setRadius(ATKRadius);
        boatATK[index].setOrigin(ATKRadius, ATKRadius);
        BiggerATKCD.restart();
    }
}

void Boat::BoatTakeDamage(int PlayerDamage) {
    BoatLife -= PlayerDamage;
}

void Boat::BoatATKTakeDamage(int PlayerDamage) {
    BoatATKLife -= PlayerDamage;
}

#pragma endregion ClassBateau

void Boss::CreateSharkBoss() {
    life = 40;
    damage = 1;
    RequinBossShape.setSize(Vector2f(350, 350));
    RequinBossShape.setPosition(1400, 700);
    RequinBossShape.setFillColor(Color::Green);
}

void Boss::MoveBoss() {
    float currentY = RequinBossShape.getPosition().y;
    if (CanMoove) {
        if (currentY >= 750) {
            movingDown = false;
        }
        else if (currentY <= 470) {
            movingDown = true;
        }

        if (movingDown) {
            RequinBossShape.move(0, 5);
        }
        else {
            RequinBossShape.move(0, -5);
        }
    }    
}

void Boss::BasicBossATK(Vector2f playerpos) {
    for (int i = 0; i < 10; i++) {
        SharkBossBulle.push_back(new bullet(playerpos, Vector2f(RequinBossShape.getPosition().x, RequinBossShape.getPosition().y + i *20)));
        for (auto& projectile : SharkBossBulle)
        {
            if (projectile->shape.getPosition().x == 0 && projectile->shape.getPosition().y == 0)
            {
                projectile->init(RequinBossShape.getPosition().x, RequinBossShape.getPosition().y);
            }
        }
    }           
}

void Boss::SecondaryBossATK() {
    Shields.clear();

    std::vector<sf::Vector2f> positions = {
        {1200, 570},
        {1200, 770},
        {1200, 970}
    };

    for (const auto& position : positions) {
        sf::CircleShape shield;
        shield.setFillColor(sf::Color(2, 127, 144));
        shield.setPosition(position);
        shield.setRadius(100);
        shield.setOrigin(100, 100);
        Shields.push_back(shield);
    }
}

void Boss::PrimaryATKDelete(size_t bullesbossindex) {
    SharkBossBulle.erase(SharkBossBulle.begin() + bullesbossindex);
}

void Boss::SecondayBossTakeDamage(size_t shieldsindex) {
    if (shieldsindex < Shields.size()) {
        Shields[shieldsindex].setOrigin(Shields[shieldsindex].getRadius()/2, Shields[shieldsindex].getRadius()/2);
        Shields[shieldsindex].setRadius(Shields[shieldsindex].getRadius()/2);
        if (Shields[shieldsindex].getRadius() <= 12.5) {
            Shields.erase(Shields.begin() + shieldsindex);
        } 
    }
}

void Boss::SecondaryBossDestroy(size_t shieldsindex) {
    Shields.erase(Shields.begin() + shieldsindex);
}

void Boss::SpecialBossATK() {
    CanMoove = false;
    RequinBossShape.setPosition(1400, (player.PlayerSprite.getPosition().y - 200));
    RequinBossShape.move(-7, 0);
}

void Boss::BossTakeDamage(int playerDamage,int DifficultyIndex) {
    life -= playerDamage;
    if (life <= 15) {
        switch (DifficultyIndex) {
        case 1:
            ATKCD = 3;
            break;
        case 2:
            ATKCD = 2;
            break;
        case 3:
            ATKCD = 1.5;
            break;
        }

    }
    if (life <= 0) {
        BossCreated = false;
        RequinBossShape.setPosition(5000, 5000);
    }
}

void Boss::SpecialBossATKMove() {
    if (isSpecialATK) {
        if (RequinBossShape.getPosition().x >= 0) {
            RequinBossShape.move(-40, 0);
        }
        else {
            isSpecialATK = false;
        }
    }
}
void Boss::SpecialBossBackward(RenderWindow& window){
    if (RequinBossShape.getPosition().x <= 1400) {
        RequinBossShape.move(20, 0);
        //window.setPosition(sf::Vector2i(0 + rand() % 25, 0 + rand() % 25));
    }
    CanMoove = true;
}