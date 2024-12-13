#include "Player.h"

extern SkillMenu sMenu;

using namespace sf;
void Player::SetDifficulty(int DifficultyIndex) {
	switch (DifficultyIndex) {
	case 1:
		Life = 5;
		break;
	case 2:
		Life = 3;
		break;
	case 3:
		Life = 1;
		break;
	}
}

void Player::InitializePlayer() {
	
	PlayerSprite.setPosition(100, 600);
	whaleTexture.loadFromFile("assets/blue-whale.png");
	PlayerSprite.setTexture(whaleTexture);
	PlayerSprite.setTextureRect(sf::IntRect(0, 0, 64, 50));
	PlayerSprite.setOrigin(60, 25);
	PlayerSprite.setScale(3, 3);

	Life = 5;
	Speed = 10.f;
	ProjectileSpeed = 0.3f;
	PlayerDamage = 1;
	MetalScrap = 0;
}

void Player::CreateBulles() {
	bulles.push_back(CircleShape());
	bulles.back().setRadius(10);
	bulles.back().setOrigin(10, 10);
	bulles.back().setFillColor(Color::Blue);
	bulles.back().setPosition(PlayerSprite.getPosition());
	timers1.push_back(Clock());
}

void Player::DeleteBulles() {
	std::cout << "delete proj" << std::endl;
	bulles.erase(bulles.begin());
	angles.erase(angles.begin());
	timers1.erase(timers1.begin());
	std::cout << "delete proj fini" << std::endl;
}

void Player::CreateWave() {
	wave.push_back(CircleShape());
	wave.back().setRadius(500);
	wave.back().setFillColor(Color(175, 85, 197));
	wave.back().setOrigin(500, 500);
	wave.back().setPosition(PlayerSprite.getPosition());
	timers2.push_back(Clock());
}

void Player::DeleteWave() {
	wave.erase(wave.begin());
	angles.erase(angles.begin());
	timers2.erase(timers2.begin());
}

void Player::TakeDamage() {
	Life -= 1;
}