#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Shark {
public:
	std::vector<sf::RectangleShape> sharks;

	int Life;
	float Speed;
	bool SharkCreated = false;

	void CreateShark(int MeleeSharks, int DistanceSharks);

	void draw(sf::RenderWindow& window);

	void moveAll();
};