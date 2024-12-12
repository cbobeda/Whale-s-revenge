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
	std::vector<SharkEnnemy> sharks;
	std::vector<sf::Vector2f> pojectileAngle;

	sf::Clock EnnemyATKCD;

	void CreateShark(int MeleeSharks, int DistanceSharks);

	void draw(sf::RenderWindow& window);

	void moveAll(sf::Vector2f playerpos);

	bool takeDamage(size_t sharkIndex,int damage);

	void SharkATK(sf::Vector2f playerpos);

	void DeleteAll();

	void DeleteATK();
};

class Boat {
public:

	struct BoatEnnemy {
		sf::RectangleShape boatshape;
		int life;
		float Speed;

		BoatEnnemy(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position, int Life, float Speed) : life(Life), Speed(Speed) {
			boatshape.setSize(size);
			boatshape.setFillColor(color);
			boatshape.setPosition(position);
		}
	};

	std::vector<BoatEnnemy> boats;
	
	sf::Clock BoatsATK;

	void CreateBoats(int BoatNumber);
	void DrawBoat(sf::RenderWindow& window);
	void MoveBoat();
	void BoatATK();
	void BoatTakeDamage();
};