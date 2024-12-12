#pragma once
#include <SFML/Graphics.hpp>
class bullet
{
private:
    sf::Vector2f player_pos;
    sf::Vector2f ennemy_pos;
public:
    bullet(sf::Vector2f player_pos,sf::Vector2f ennemy_pos): player_pos(player_pos), ennemy_pos(ennemy_pos) {};
    ~bullet() {};
    sf::CircleShape shape;
    void init(int x, int y);
    sf::Vector2f normalize(const sf::Vector2f& vector);
    void update(float speed);
};
