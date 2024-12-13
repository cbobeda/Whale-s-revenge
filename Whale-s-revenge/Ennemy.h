#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "bullet.h"

class Shark {
public:
	std::vector<bullet*> ennemyATK;
	sf::Texture requin_texture;
	sf::Sprite shape;
	sf::RectangleShape rect;
	int life;
	bool isRanged;
	int ProjectileSpeed = 20;

	Shark(const sf::Vector2f& size, const sf::Vector2f& position,int initialLife, bool ranged): life(initialLife), isRanged(ranged) {
		rect.setSize(sf::Vector2f(130,130));
		rect.setFillColor(sf::Color::White);
		rect.setPosition(position);
		shape.setScale(size);
		shape.setPosition(position);
	}
	int projectileSpeed = 20;	
	

	sf::Clock EnnemyATKCD;

	void CreateShark(int MeleeSharks, int DistanceSharks);

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
    sf::RectangleShape boatshape;
    int life;
    float Speed = -8;
    bool hasAttacked;
    int attackDelay;
    sf::Clock attackTimer;

    std::vector<sf::CircleShape> boatATK;  
    sf::Clock BoatsATK;
    sf::Clock BiggerATKCD; 

    Boat(const sf::Vector2f& size, const sf::Color& color, const sf::Vector2f& position, int Life, float Speed)
        : life(Life), Speed(Speed), hasAttacked(false) {
        boatshape.setSize(size);
        boatshape.setFillColor(color);
        boatshape.setPosition(position);
        attackDelay = (rand() % 10 + 1) * 1000;  
    }

    void CreateBoats(int BoatNumber); 
    void MoveBoat();  
    void BoatATK();  
    void BiggerATK(size_t index); 
    void BoatTakeDamage(int PlayerDamage); 
    void BoatATKTakeDamage(int PlayerDamage);

};