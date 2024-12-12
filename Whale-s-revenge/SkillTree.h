#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"

class SkillMenu {
public:
	bool isUpgrading = false;
	void DisplaySkillMenu(sf::RenderWindow& window);
	void switchUpgrading();
};