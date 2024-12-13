#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
#include "Player.h"

class SkillMenu {
public:
	bool isUpgrading = false;
	bool SecondaryUnlocked = false;
	bool PrimaryUpgraded = false;
	bool SecondaryUpgraded = false;
	
	int PrimaryIndex;
	int SecondaryIndex;

	void DisplaySkillMenu(sf::RenderWindow& window);
	void switchUpgrading();
};