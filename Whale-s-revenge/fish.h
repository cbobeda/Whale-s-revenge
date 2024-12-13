#pragma once
#include "Player.h"
class fish
{
private:
    int x;
    int y;
    int liferegen;
public:
    fish(int posX,int posY, int liferegen): x(posX), y(posY), liferegen(liferegen){};
    ~fish() {};
    void colide(Player player);
};
