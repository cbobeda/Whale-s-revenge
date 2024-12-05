#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Player.h"

using namespace sf;


void Player::InitializePlayer() {
	
	PlayerSprite.setPosition(100, 600);
	PlayerSprite.setFillColor(sf::Color::Cyan);
	PlayerSprite.setOrigin(25, 25);
	PlayerSprite.setRadius(25);

	Life = 5;
	Speed = 10.f;
	ProjectileSpeed = 0.3f;
}

void Player::CreateBulles() {
	bulles.push_back(CircleShape());
	bulles.back().setRadius(10);
	bulles.back().setOrigin(10, 10);
	bulles.back().setFillColor(Color::Blue);
	bulles.back().setPosition(PlayerSprite.getPosition());
	timers.push_back(Clock());
	
}

void Player::DeleteBulles() {
	bulles.erase(bulles.begin());
	angles.erase(angles.begin());
	timers.erase(timers.begin());
}