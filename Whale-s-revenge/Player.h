#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player {
public:

	std::vector<sf::CircleShape> bulles;
	std::vector<sf::RectangleShape> wave;

	std::vector<float> angles;

	std::vector<sf::Clock> timers1;
	std::vector<sf::Clock> timers2;

	sf::CircleShape PlayerSprite;
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
};