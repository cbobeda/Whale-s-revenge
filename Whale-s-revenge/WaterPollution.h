#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Pollution {
private:
	int pollustate = 0;
	int minimumPollu = 0;

	int surplus;

public:

	void IncreasePollution(int DifficultyIndex);
	void DecreasePollution();
	void IncreaseMinimum(int Increase);
	void DecreaseMinimum(int Decrease);
	void MaximumReach();
};