#include "Main menu.h"

button play_button(100,100,150,150);
bool active = true;
bool frame = false;
bool isready = false;
Clock watch;
float frameDuration = 1.0f; // Durée d'une frame (en secondes)
size_t currentFrame = 0;
bool Main_menu::mdisplay(RenderWindow& window)
{
    

    Texture background;
    if (frame)
    {
        background.loadFromFile("menu1.png");

    }
    else
    {
        background.loadFromFile("menu2.png");

    }
    float scalex = window.getSize().x / background.getSize().x;
    float scaley = window.getSize().y / background.getSize().y;
    Sprite background_sprite;
    background_sprite.setTexture(background);
    background_sprite.setScale(scalex, scaley);
    window.draw(background_sprite);
    window.draw(play_button.bdisplay(Color::Red,Color::Black));
    if (play_button.check(Mouse::getPosition().x, Mouse::getPosition().y) && Mouse::isButtonPressed(Mouse::Left))
    {
        active = false;
    }
    if (!active)
        window.clear();
    if (watch.getElapsedTime().asSeconds() > frameDuration) {
        if (frame)
        {
            frame = false;
        }
        else
        {
            frame = true;
        }
        watch.restart();
    }
    return active;
}
