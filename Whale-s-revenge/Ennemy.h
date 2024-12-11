#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Shark {
public:

	std::vector<sf::CircleShape> ennemyATK;

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
	std::vector<float> pojectileAngle;

	sf::Clock EnnemyATKCD;

	void CreateShark(int MeleeSharks, int DistanceSharks);

	void draw(sf::RenderWindow& window);

	void moveAll();

	bool takeDamage(size_t sharkIndex,int damage);

	void SharkATK();

	void DeleteAll();

	void DeleteATK(size_t index);
};

class Boat {
public:

	struct BoatEnnemy {
		sf::RectangleShape boatshape;
		int life;
		float Speed;
		bool hasAttacked;
		int attackDelay;
		sf::Clock attackTimer;

		BoatEnnemy(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position, int Life, float Speed)
			: life(Life), Speed(Speed), hasAttacked(false) {
			boatshape.setSize(size);
			boatshape.setFillColor(color);
			boatshape.setPosition(position);

			attackDelay = (rand() % 15 + 1) * 1000;
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