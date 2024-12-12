#include <SFML/Graphics.hpp>
#include "button.h"
#include <iostream>
using namespace sf;
extern button play_button;
class Main_menu
{
private:
    int height;
    int width;
    
public:
    Main_menu(int h,int w): height(h),width(w) {};
    int DifficultyIndex = 2;
    bool mdisplay(sf::RenderWindow& window,Event event);
    void actmenu();
};
