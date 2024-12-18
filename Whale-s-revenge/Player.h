#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include "SkillTree.h"

class Player {
public:

	std::vector<sf::Sprite> bulles;
	std::vector<sf::CircleShape> wave;

	std::vector<float> angles;

	std::vector<sf::Clock> timers1;
	std::vector<sf::Clock> timers2;

	sf::Texture whaleTexture;
	sf::Sprite PlayerSprite;

	sf::Clock InvicibleFrame;
	sf::Clock InvicibleFramShow;

	int Life;
	float Speed;
	float ProjectileSpeed;
	float ProjectileCD;
	int PlayerDamage;
	int MetalScrap;

	bool CanSecondary = false;
	bool ShowPlayer = true;

	void InitializePlayer();
	void CreateBulles();
	void DeleteBulles();
	void CreateWave();
	void DeleteWave();
	void TakeDamage();
	void SetDifficulty(int DifficultyIndex);
	void ChangeShowValue();
};