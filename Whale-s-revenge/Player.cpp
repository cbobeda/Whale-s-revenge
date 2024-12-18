#include "Player.h"

extern SkillMenu sMenu;

using namespace sf;

Texture texture;
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
	PlayerSprite.setScale(2.5, 2.5);

	Life = 5;
	Speed = 10.f;
	ProjectileSpeed = 20.f;
	ProjectileCD = 0.4;
	PlayerDamage = 1;
	MetalScrap = 0;
}

void Player::CreateBulles() {
	texture.loadFromFile("assets/pearl.png");
	Sprite bulle;
	bulle.setTexture(texture);
	bulles.push_back(bulle);
	bulles.back().setOrigin(10, 10);
	bulles.back().setColor(Color(212,243,248,255));
	bulles.back().setPosition(PlayerSprite.getPosition());
	timers1.push_back(Clock());
}

void Player::DeleteBulles() {
	bulles.erase(bulles.begin());
	angles.erase(angles.begin());
	timers1.erase(timers1.begin());
}

void Player::CreateWave() {
	texture.loadFromFile("assets/pearl.png");
	wave.push_back(CircleShape());
	Sprite bulle;
	bulle.setTexture(texture);
	wave.back().setRadius(80);
	wave.back().setFillColor(Color(175, 85, 197));
	wave.back().setOrigin(80, 80);
	wave.back().setPosition(PlayerSprite.getPosition());
	timers2.push_back(Clock());
}

void Player::DeleteWave() {
	wave.erase(wave.begin());
	angles.erase(angles.begin());
	timers2.erase(timers2.begin());
}

void Player::TakeDamage() {
	if (InvicibleFrame.getElapsedTime().asSeconds() > 1) {
		Life -= 1;
		InvicibleFrame.restart();
	}
}

void Player::ChangeShowValue() {
	if (ShowPlayer) {
		ShowPlayer = false;
	}
	else {
		ShowPlayer = true;
	}
}
