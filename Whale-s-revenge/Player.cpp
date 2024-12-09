#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <string>
#include "Player.h"

using namespace sf;


void Player::InitializePlayer() {
	
	PlayerSprite.setPosition(100, 600);
	whaleTexture.loadFromFile("blue-whale.png");
	PlayerSprite.setTexture(whaleTexture);
	PlayerSprite.setTextureRect(sf::IntRect(0, 0, 64, 50));
	PlayerSprite.setOrigin(25, 25);
	PlayerSprite.setScale(2, 2);

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
	bulles.erase(bulles.begin());
	angles.erase(angles.begin());
	timers1.erase(timers1.begin());
}

void Player::CreateWave() {
	wave.push_back(RectangleShape());
	wave.back().setSize(Vector2f(100, 400));
	wave.back().setOrigin(50, 200);
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