#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Ennemy.h"
#include <cstdlib>

using namespace sf;
	
void Shark::CreateShark(int MeleeSharks, int DistanceSharks) {
    const int meleeLife = 4;
    const int distanceLife = 3;

    for (int i = 0; i < MeleeSharks; i++) {
        sharks.emplace_back(sf::Vector2f(150, 75),sf::Color::Red,sf::Vector2f(2200, rand() % 400 + 400), meleeLife, false);
    }

    for (int j = 0; j < DistanceSharks; j++) {
        sharks.emplace_back(sf::Vector2f(150, 75),sf::Color::Green,sf::Vector2f(1800, rand() % 400 + 400), distanceLife, true);
    }

    SharkCreated = true;
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
                if (shark.shape.getPosition().x > 1000) {
                    shark.shape.move(-5, 0); 
                }
                else {
                        SharkATK();
                    
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
            ennemyATK.back().setRadius(5);
            ennemyATK.back().setOrigin(5, 5);
            ennemyATK.back().setFillColor(Color::Yellow);
            ennemyATK.back().setPosition(shark.shape.getPosition());
        }
    }
}