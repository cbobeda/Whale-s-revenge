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

void Shark::CreateShark(int MeleeSharks, int DistanceSharks) {
    int meleeLife = 4;
    int distanceLife = 3;
    
    for (int i = 0; i < MeleeSharks; i++) {
        sharksvect.emplace_back(sf::Vector2f(5, 5),sf::Vector2f(rand() % 2200 + 2000, rand() % 600 + 300),meleeLife, false);
    }

    for (int j = 0; j < DistanceSharks; j++) {
        sharksvect.emplace_back(sf::Vector2f(5, 5),sf::Vector2f(rand() % 2500 + 2000, rand() % 600 + 300),distanceLife, true);
        
    }
}

    void Shark::moveAll(Vector2f playerpos) {
        for (auto& shark : sharksvect) {
            if (!shark.isRanged) {
                shark.shape.move(-5, 0);
            }
            else {
                if (shark.shape.getPosition().x > 1700) {
                    shark.shape.move(-5, 0); 
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
    for (int i = 0 ; i < sharksvect.size(); i++) {
        if (sharksvect[i].isRanged) {
            ennemyATK.push_back(new bullet(playerpos,sharksvect[i].shape.getPosition()));
            for (auto& projectile : ennemyATK)
            {
                if (projectile->shape.getPosition().x == 0 && projectile->shape.getPosition().y == 0)
                {
                    projectile->init(sharksvect[i].shape.getPosition().x,sharksvect[i].shape.getPosition().y);
                }
            }
        }
    }
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
std::vector<Boat> Boat::boats;

void Boat::CreateBoats(int BoatNumber) {
    int BaseBoatSpawn = 2200;
    for (int i = 0; i < BoatNumber; i++) {
        BaseBoatSpawn += (rand() % 900) + 1000;

        boats.emplace_back(sf::Vector2f(100, 50), sf::Color(38, 182, 122), sf::Vector2f(BaseBoatSpawn, 400), 5, 10);
    }
}

void Boat::MoveBoat() {
    for (auto& boat : boats) {
        boat.boatshape.move(-8, 0);
    }
}

void Boat::BoatATK() {
    for (auto& boat : boats) {
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