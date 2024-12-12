#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "bullet.h"

class Shark {
public:
	std::vector<bullet*> ennemyATK;
	
	struct SharkEnnemy {
		sf::RectangleShape shape;
		int life;
		bool isRanged;

		SharkEnnemy(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position, int initialLife, bool ranged): life(initialLife), isRanged(ranged) {
			shape.setSize(size);
			shape.setFillColor(color);
			shape.setPosition(position);
		}
		
	};

	int projectileSpeed;
	std::vector<SharkEnnemy> sharks;
	std::vector<sf::Vector2f> pojectileAngle;

	sf::Clock EnnemyATKCD;

	void CreateShark(int MeleeSharks, int DistanceSharks);

	void draw(sf::RenderWindow& window);

	void moveAll(sf::Vector2f playerpos);

	bool takeDamage(size_t sharkIndex,int damage);

	void SharkATK(sf::Vector2f playerpos);

	void DeleteAll();

	void DeleteATK(size_t index);

	void SetDifficulty(int DifficultyIndex);
};

class Boat {
public:

	int ATKRadius = 50;
	int BoatLife = 5;
	int BoatATKLife = 10;

	struct BoatEnnemy {
		sf::RectangleShape boatshape;
		int life;
		float Speed;
		bool hasAttacked;
		int attackDelay;
		sf::Clock attackTimer;

		BoatEnnemy(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position, int Life, float Speed): life(Life), Speed(Speed), hasAttacked(false) {
			boatshape.setSize(size);
			boatshape.setFillColor(color);
			boatshape.setPosition(position);

			attackDelay = (rand() % 10 + 1) * 1000;
		}
	};

	std::vector<BoatEnnemy> boats;
	std::vector<sf::CircleShape> boatATK;
	
	sf::Clock BoatsATK;
	sf::Clock BiggerATKCD;

	void CreateBoats(int BoatNumber);
	void DrawBoat(sf::RenderWindow& window);
	void MoveBoat();
	void BoatATK();
	void BoatTakeDamage(int PlayerDamage);
	void BiggerATK(size_t index);
	void BoatATKTakeDamage(int PlayerDamage);
};