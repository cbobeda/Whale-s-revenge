#include "fish.h"

void fish::fishupdate()
{
    this->sprite.move(-10,0);
    if(this->sprite.getPosition().x<0)
    {
        this->sprite.setPosition(2000 + rand() % 1000, 500 + rand() % 600);
        this->sprite.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255,255));
    }
}

