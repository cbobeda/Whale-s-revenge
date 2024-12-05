#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Shark {
public:
	std::vector<sf::RectangleShape> sharks;

	int Life;
	float Speed;

	void CreateShark();
};