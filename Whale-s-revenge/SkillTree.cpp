#include "SkillTree.h"

using namespace sf;

button BaseUpgrade(100, 500, 175, 175, false);
button SecondaryUnlock(400, 500, 175, 175, true);
button PrimaryMagic(900, 200, 175, 175, false);
button SecondaryMagic(1100, 200, 175, 175, false);
button PrimaryTechno(900, 800, 175, 175, false);
button SecondaryTechno(1100, 800, 175, 175, false);

extern Player player;

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
		BaseUpgrade.bdisplay(Color(180,248,206), Color::Black, window, 10, "Primary");
		SecondaryUnlock.bdisplay(Color::Yellow, Color::Black, window, 10, "Secondary");
		PrimaryMagic.bdisplay(Color(48,218,220), Color::Black, window, 10, "Primary");
		SecondaryMagic.bdisplay(Color(40,187,190), Color::Black, window, 10, "Secondary");
		PrimaryTechno.bdisplay(Color(221,158,49), Color::Black, window, 10, "Primary");
		SecondaryTechno.bdisplay(Color(185,132,40), Color::Black, window, 10, "Secondary");
	}

	if (SecondaryUnlock.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left)){
		if (player.MetalScrap >= 100 && !SecondaryUnlocked) {
			SecondaryIndex = 1;
			player.MetalScrap -= 100;
			SecondaryUnlocked = true;
			SecondaryUnlock.setclicked();
			player.Life += 1;
			std::cerr << "Upgrade" << std::endl;
		}
	}
}