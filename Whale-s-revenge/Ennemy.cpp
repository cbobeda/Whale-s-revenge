#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Ennemy.h"
#include <cstdlib>

using namespace sf;

#pragma region ClassRequin
void Shark::CreateShark(int MeleeSharks, int DistanceSharks) {
    const int meleeLife = 4;
    const int distanceLife = 3;

    for (int i = 0; i < MeleeSharks; i++) {
        sharks.emplace_back(sf::Vector2f(150, 75),sf::Color::Red,sf::Vector2f(rand() % 2200 + 2000, rand() % 600 + 300), meleeLife, false);
    }

    for (int j = 0; j < DistanceSharks; j++) {
        sharks.emplace_back(sf::Vector2f(150, 75),sf::Color::Green,sf::Vector2f(rand() % 2500 + 2000, rand() % 600 + 300), distanceLife, true);
    }
}

void Shark::draw(sf::RenderWindow& window) {
	for (const auto& shark : sharks) {
		window.draw(shark.shape);
	}
}

    void Shark::moveAll() {
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
                        SharkATK();
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

void Shark::SharkATK() {
    for (auto& shark : sharks) {
        if (shark.isRanged) {
            ennemyATK.push_back(CircleShape());
            ennemyATK.back().setRadius(10);
            ennemyATK.back().setOrigin(10, 10);
            ennemyATK.back().setFillColor(Color::Yellow);
            ennemyATK.back().setPosition(shark.shape.getPosition());



        }
    }
}

void Shark::DeleteAll() {
        sharks.clear();
        ennemyATK.clear();
}

void Shark::DeleteATK() {
    ennemyATK.erase(ennemyATK.begin());
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
    for (const auto& boat : boats) {
        window.draw(boat.boatshape);
    }
}

void Boat::MoveBoat() {
    for (auto& boat : boats) {
        boat.boatshape.move(-8, 0);
    }
}

void Boat::BoatATK() {

}
void Boat::BoatTakeDamage() {

}
#pragma endregion ClassBateau