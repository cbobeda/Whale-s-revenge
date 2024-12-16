#include "bonus.h"
#include <random>


void bonus::checkCollision(Player &player)
{
    rect.move(-5,0);
    if (player.PlayerSprite.getGlobalBounds().intersects(this->rect.getGlobalBounds()))
    {
        player.Life += 1;
        rect.setPosition(2000 + rand() % 4000, 500 + rand() % 600 );
        std::cerr << player.Life << std::endl;
    }
}
