#include <SFML/Graphics.hpp>
#include "button.h"
#include <iostream>
#include "Ennemy.h"
using namespace sf;
extern button selectmenu_button;
extern Shark sharks;

enum MenuIndex { MainMenu, LevelMenu, CustomMenu, GameOver , Campagne};

extern MenuIndex menuindex;

class Main_menu
{
private:
    int height;
    int width;

public:
    Main_menu(int h, int w) : height(h), width(w) {};

    int DifficultyIndex = 2;
    int nbMeleeEnnemy = 0;
    int nbDistanceEnnemy = 0;

    bool isPlayingCustom = false;

    bool mdisplay(sf::RenderWindow& window, Event event);
    void actmenu();
};
