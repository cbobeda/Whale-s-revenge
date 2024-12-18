#include "WaterPollution.h"

void Pollution::IncreaseMinimum(int Increase) {
	minimumPollu += Increase;
	if (pollustate < minimumPollu) {
		pollustate = minimumPollu;
	}
}

void Pollution::DecreaseMinimum(int Decrease) {
	minimumPollu -= Decrease;
	if (minimumPollu < 0) {
		surplus = 0 - minimumPollu;
		minimumPollu += surplus;
	}
}

void Pollution::IncreasePollution(int DifficultyIndex) {
	pollustate += 1 + DifficultyIndex;

	if (pollustate >= 100) {
		MaximumReach();
	}
}

void Pollution::DecreasePollution() {
	if (pollustate > minimumPollu) {
		pollustate -= 1;
	}	
}

void Pollution::MaximumReach() {
	//GameOver
}
