#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player {
public:

	std::vector<sf::CircleShape> bulles;
	std::vector<float> angles;
	std::vector<sf::Clock> timers;

	sf::CircleShape PlayerSprite;
	int Life;
	float Speed;
	float ProjectileSpeed;

	void InitializePlayer();
	void CreateBulles();
	void DeleteBulles();
};