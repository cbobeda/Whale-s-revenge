#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Pollution {
private:
	int minimumPollu = 0;

	int surplus;

public:

	sf::Clock PollutionClock;

	int pollustate = 0;

	bool isPolluting = false;
	bool CanChange = false;

	void IncreasePollution(int DifficultyIndex);
	void DecreasePollution();
	void IncreaseMinimum(int Increase);
	void DecreaseMinimum(int Decrease);
	void MaximumReach();
};