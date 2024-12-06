#include <SFML/Graphics.hpp>

class button
{
private:
    int posX;
    int posY;
    int width;
    int height;
    
public:
    button(int x,int y,int w, int h): posX(x),posY(y),width(w),height(h) {};
    
    ~button() {};
    bool check(int x,int y,sf::RenderWindow& window);
    sf::RectangleShape bdisplay(sf::Color couleur,sf::Color couleur2);
};