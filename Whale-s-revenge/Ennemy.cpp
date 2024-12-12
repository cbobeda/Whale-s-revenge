#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Ennemy.h"
#include <cstdlib>

using namespace sf;
#pragma region ClassRequin
extern std::vector<Shark> sharksvect;
void Shark::CreateShark(int MeleeSharks, int DistanceSharks) {
    const int meleeLife = 4;
    const int distanceLife = 3;
    
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

void Boat::CreateBoats(int BoatNumber) {
    int BaseBoatSpawn = 2200;
    for (int i = 0; i < BoatNumber; i++) {
        BaseBoatSpawn += (rand() % 900) + 1000;

        boats.emplace_back(sf::Vector2f(100, 50), sf::Color(38, 182, 122), sf::Vector2f(BaseBoatSpawn, 400), 5, 10);
    }
}

void Boat::DrawBoat(sf::RenderWindow& window) {
    for (auto& boat : boats) {
        window.draw(boat.boatshape);
    }
}

void Boat::MoveBoat() {
    for (auto& boat : boats) {
        boat.boatshape.move(-8, 0);
    }
}

void Boat::BoatATK() {
    for (size_t i = 0; i < boats.size(); i++) {
        auto& boat = boats[i];

        if (!boat.hasAttacked && boat.boatshape.getPosition().x < 1900 && boat.boatshape.getPosition().x > 0) {
            if (boat.attackTimer.getElapsedTime().asMilliseconds() >= boat.attackDelay) {
                boatATK.push_back(CircleShape());
                boatATK.back().setFillColor(Color(161,229,54));
                boatATK.back().setPosition(boat.boatshape.getPosition());
                boatATK.back().setRadius(ATKRadius);
                boatATK.back().setOrigin(ATKRadius, ATKRadius);

                boat.hasAttacked = true;
            }
        }
    }
}

void Boat::BiggerATK(size_t index) {
    for (size_t i = 0; i < boatATK.size(); i++) {
        if (BiggerATKCD.getElapsedTime().asSeconds() > 0.1) {
            ATKRadius += 5;
            boatATK[index].setRadius(ATKRadius);
            boatATK[index].setOrigin(ATKRadius, ATKRadius);
            BiggerATKCD.restart();
        }

    }
}

void Boat::BoatTakeDamage() {

}

#pragma endregion ClassBateau