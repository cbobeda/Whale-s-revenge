#include "SkillTree.h"

using namespace sf;

button BaseUpgrade(100, 500, 100, 100, false);
button SecondaryUnlock(400, 500, 100, 100, false);
button PrimaryMagic(900, 200, 100, 100, false);
button SecondaryMagic(1100, 200, 100, 100, false);
button PrimaryTechno(900, 800, 100, 100, false);
button SecondaryTechno(1100, 800, 100, 100, false);

void SkillMenu::switchUpgrading() {
	if (isUpgrading) {
		isUpgrading = false;
	}
	else {
		isUpgrading = true;
	}
}

void SkillMenu::DisplaySkillMenu(RenderWindow& window) {
	if (isUpgrading) {
		BaseUpgrade.bdisplay(Color::Yellow, Color::Black, window, 10, "Base");
	}
}