#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
class fish
{
private:
    int x;
    int y;
    sf::Texture texture;
public:
    sf::Sprite sprite;
    fish(){texture.loadFromFile("assets/fish.png");sprite.setTexture(texture);sprite.setPosition(sf::Vector2f(2000,500));};
    ~fish() {};
    void fishupdate();
};
