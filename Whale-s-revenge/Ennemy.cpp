#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Ennemy.h"
#include <cstdlib>

using namespace sf;
	
void Shark::CreateShark(int MeleeSharks,int DistanceSharks) {
	for (int i = 0; i < MeleeSharks; i++) {
		sharks.push_back(RectangleShape());
		sharks.back().setSize(Vector2f(150, 75));
		sharks.back().setFillColor(Color::Red);
		sharks.back().setPosition(800, (rand() % 800 + 400));
	}
	for (int j = 0; j < DistanceSharks; j++) {
		sharks.push_back(RectangleShape());
		sharks.back().setSize(Vector2f(150, 75));
		sharks.back().setFillColor(Color::Green);
		sharks.back().setPosition(1400, (rand() % 800 + 400));
	}

	Shark::SharkCreated = true;
}

void Shark::draw(sf::RenderWindow& window) {
	for (const auto& shark : sharks) {
		window.draw(shark);
	}
}

void Shark::moveAll() {
	for (auto& shark : sharks) {
		shark.move(-5, 0);
	}
}