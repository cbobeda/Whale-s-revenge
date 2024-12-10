#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

class button
{
private:
    int posX;
    int posY;
    int width;
    int height;
    bool tcheck;
    bool clicked;
    
public:
    button(int x,int y,int w, int h,bool c): posX(x),posY(y),width(w),height(h),tcheck(c),clicked(false) {};
    
    ~button() {};
    bool check(int x,int y,sf::RenderWindow& window);
    void setclicked(bool reset = false);
    void bdisplay(sf::Color couleur,sf::Color couleur2,sf::RenderWindow& window,int size,sf::String isText = "");
};