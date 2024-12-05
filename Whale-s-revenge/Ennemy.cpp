#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Ennemy.h"
#include <cstdlib>

using namespace sf;
	
void Shark::CreateShark() {
	sharks.push_back(RectangleShape());
	sharks.back().setSize(Vector2f(150, 75));
	sharks.back().setFillColor(Color::Red);
	sharks.back().setPosition(1400, (rand() % 800 + 200));
	}