#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "bullet.h"
#include "WaterPollution.h"

using namespace sf;
extern Player player;
extern Pollution pollution;

class Shark {
public:
    std::vector<bullet*> ennemyATK;
    sf::Texture requin_texture;
    sf::Sprite shape;
    sf::RectangleShape rect;
    int life;
    bool isRanged;
    int ProjectileSpeed = 20;
    float Speed = -6;

    Shark(const sf::Vector2f& size, const sf::Vector2f& position, int initialLife, bool ranged) : life(initialLife), isRanged(ranged) {
        rect.setSize(sf::Vector2f(130, 130));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(position);
        shape.setScale(size);
        shape.setPosition(position);
    }


    sf::Clock EnnemyATKCD;

    void CreateShark(int MeleeSharks, int DistanceSharks, int MLife, int DLife);

    void moveAll(sf::Vector2f playerpos);

    bool takeDamage(size_t sharkIndex, int damage);

    void SharkATK(sf::Vector2f playerpos);

    void DeleteAll();
    void DeleteShark(size_t sharkindex);
    void DeleteATK(size_t index);

    void SetDifficulty(int DifficultyIndex);
};

class Boat {
private:
    sf::Texture boat_texture;    
public:
    int ATKRadius = 50;
    int BoatLife = 5;
    int BoatATKLife = 10;
    sf::Sprite boatshape;
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
        boat_texture.loadFromFile("assets/boat.png");
        boatshape.setTexture(boat_texture);
        boatshape.setScale(2,2);
        boatshape.setPosition(position);
        attackDelay = (rand() % 5 + 1) * 1000;
    }

    void CreateBoats(int BoatNumber);
    void MoveBoat();
    void BoatATK();
    void DestroyBoat(size_t boatindex);
    void BiggerATK(size_t index);
    void BoatTakeDamage(int PlayerDamage);
    void BoatATKTakeDamage(int PlayerDamage);

};

class Boss {
public:
    int life;
    int damage;
    int ATKCD = 3;
    bool movingDown = true;
    bool CanMoove = true;
    bool BossCreated = false;

    bool isSpecialATK = false;
    sf::Texture Bossrequin_texture;
    sf::Sprite RequinBossShape;
    std::vector<bullet*> SharkBossBulle;
    std::vector<sf::CircleShape> Shields;

    sf::Clock SharkBossCD;

    void CreateSharkBoss();
    void MoveBoss();
    void BasicBossATK(Vector2f playerpos);
    void PrimaryATKDelete(size_t bullesbossindex);
    void BossTakeDamage(int playerDamage, int DifficultyIndex);
    void SecondaryBossATK();
    void SecondayBossTakeDamage(size_t shieldsindex);
    void SecondaryBossDestroy(size_t shieldsindex);
    void SpecialBossATK();
    void SpecialBossATKMove();
    void SpecialBossBackward(RenderWindow& window);
};