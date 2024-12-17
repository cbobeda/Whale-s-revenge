#pragma once
#include "Player.h"
#include "Ennemy.h"
#include <SFML/Graphics.hpp>
#include <vector>


extern std::vector<Shark> sharksvect;
class bonus
{
private:
    sf::Texture texture;
public:
    sf::Sprite rect;
    bonus(int posX, int posY,int sizex,int sizey){texture.loadFromFile("assets/pearl.png");rect.setTexture(texture);rect.setPosition(sf::Vector2f(posX,posY));};
    ~bonus() {};
    void checkCollision(Player &player);
};