#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include "SkillTree.h"

class Player {
public:

	std::vector<sf::Sprite> bulles;
	std::vector<sf::CircleShape> wave;
	std::vector<sf::CircleShape> Explosion;

	std::vector<float> angles;

	std::vector<sf::Clock> timers1;
	std::vector<sf::Clock> timers2;
	std::vector<sf::Clock> timers3;

	sf::Texture whaleTexture;
	sf::Sprite PlayerSprite;

	sf::Clock InvicibleFrame;
	sf::Clock InvicibleFramShow;


	int Life;

	float Speed;
	float ProjectileSpeed;
	float ProjectileCD;
	float ProjectileSize;

	float SecondaryProjectileSpeed;
	float SecondaryProjectileCD;
	float SecondaryProjectileSize;

	int PlayerDamage;
	int MetalScrap;

	bool CanSecondary = false;
	bool ShowPlayer = true;
	bool SecondaryTechno = false;

	void InitializePlayer();
	void CreateBulles();
	void DeleteBulles();
	void CreateWave();
	void DeleteWave();
	void TakeDamage();
	void SetDifficulty(int DifficultyIndex);
	void ChangeShowValue();
	void Explode();
	void DeleteExplosion();
};