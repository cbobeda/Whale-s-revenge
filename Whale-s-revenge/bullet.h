#pragma once
#include <SFML/Graphics.hpp>
class bullet
{
private:
    sf::Vector2f player_pos;
    sf::Vector2f ennemy_pos;
    sf::Texture texture;
public:
    sf::Sprite shape;
    bullet(sf::Vector2f player_pos,sf::Vector2f ennemy_pos): player_pos(player_pos), ennemy_pos(ennemy_pos) {texture.loadFromFile("assets/pearl.png");shape.setTexture(texture);shape.setColor(sf::Color(220,255,66,255));};
    ~bullet() {};
    void init(int x, int y);
    sf::Vector2f normalize(const sf::Vector2f& vector);
    void update(float speed);
};
