#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Ennemy.h"
#include <cstdlib>

using namespace sf;
#pragma region ClassRequin

void Shark::SetDifficulty(int DifficultyIndex) {
    switch (DifficultyIndex) {
    case 1:
        projectileSpeed = 15;
        break;
    case 2:
        projectileSpeed = 20;
        break;
    case 3:
        projectileSpeed = 80;
        break;
    }
}

void Shark::CreateShark(int MeleeSharks, int DistanceSharks) {
    const int meleeLife = 4;
    const int distanceLife = 3;

    for (int i = 0; i < MeleeSharks; i++) {
        sharks.emplace_back(sf::Vector2f(150, 75),sf::Color::Red,sf::Vector2f(rand() % 2200 + 2000, rand() % 600 + 300), meleeLife, false);
    }

    for (int j = 0; j < DistanceSharks; j++) {
        sharks.emplace_back(sf::Vector2f(150, 75),sf::Color::Green,sf::Vector2f(rand() % 2500 + 2000, rand() % 600 + 300), distanceLife, true);
        
    }
    for (int o = 0; o < 100; o++) {pojectileAngle.push_back(sf::Vector2f(0, 0));}
}

void Shark::draw(sf::RenderWindow& window) {
	for (const auto& shark : sharks) {
		window.draw(shark.shape);
	}
}

    void Shark::moveAll(Vector2f playerpos) {
        for (auto& shark : sharks) {
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
    if (sharkIndex < sharks.size()) {
        sharks[sharkIndex].life -= damage;

        if (sharks[sharkIndex].life <= 0) {
            sharks.erase(sharks.begin() + sharkIndex);
            return true;
        }
    }
    return false;
}

void Shark::SharkATK(Vector2f playerpos) {
    for (int i = 0 ; i < sharks.size(); i++) {
        if (sharks[i].isRanged) {
            ennemyATK.push_back(new bullet(playerpos,sharks[i].shape.getPosition()));
            for (auto& projectile : ennemyATK)
            {
                if (projectile->shape.getPosition().x == 0 && projectile->shape.getPosition().y == 0)
                {
                    projectile->init(sharks[i].shape.getPosition().x,sharks[i].shape.getPosition().y);
                }
            }
        }
    }
}

void Shark::DeleteAll() {
        sharks.clear();
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

void Boat::BoatTakeDamage(int PlayerDamage) {
    BoatLife -= PlayerDamage;
}

void Boat::BoatATKTakeDamage(int PlayerDamage) {
    BoatATKLife -= PlayerDamage;
}

#pragma endregion ClassBateau