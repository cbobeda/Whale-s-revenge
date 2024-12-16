#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include "SkillTree.h"

class Player {
public:

	std::vector<sf::CircleShape> bulles;
	std::vector<sf::CircleShape> wave;

	std::vector<float> angles;

	std::vector<sf::Clock> timers1;
	std::vector<sf::Clock> timers2;

	sf::Texture whaleTexture;
	sf::Sprite PlayerSprite;

	sf::Clock InvicibleFrame;

	int Life;
	float Speed;
	float ProjectileSpeed;
	int PlayerDamage;
	int MetalScrap;

	void InitializePlayer();
	void CreateBulles();
	void DeleteBulles();
	void CreateWave();
	void DeleteWave();
	void TakeDamage();
	void SetDifficulty(int DifficultyIndex);
};