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

	int Life;
	bool SharkCreated = false;
	float AttackEnnemyCD;

	sf::Clock EnnemyATKCD;

	void newCD();

	void CreateShark(int MeleeSharks, int DistanceSharks);

	void draw(sf::RenderWindow& window);

	void moveAll();

	bool takeDamage(size_t sharkIndex,int damage);

	void SharkATK();
};