﻿#include <SFML/Graphics.hpp>
#include "button.h"
using namespace sf;
extern button play_button;
class Main_menu
{
private:
    int height;
    int width;
    
public:
    Main_menu(int h,int w): height(h),width(w) {};

    bool mdisplay(sf::RenderWindow& window);
};
