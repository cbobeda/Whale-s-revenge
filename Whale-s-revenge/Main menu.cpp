#include "Main menu.h"

button play_button(100,100,100,100);
button option_button(100,300,100,100);
button exit_button(100,500,100,100);
button fullscreen(500,200,100,100);
bool active = true;
bool frame = false;
bool isready = false;
bool option = false;
Clock watch;
float frameDuration = 0.5f; // Durée d'une frame (en secondes)
size_t currentFrame = 0;

void Main_menu::actmenu()
{
    if (active)
    {
        active = false;
    }
    else
    {
        active = true;
    }
}


bool Main_menu::mdisplay(RenderWindow& window)
{
    Font font;
    font.loadFromFile("MinecraftStandard.otf");
    Text text;
    text.setFont(font);
    text.setString("Whale's revenge");
    text.setCharacterSize(40);
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(5);
    text.setOrigin(262,26.5);
    text.setPosition(Vector2f(960,200));
    text.setScale(1.5,1.5);
    Text option_text;
    option_text.setFont(font);
    option_text.setCharacterSize(40);
    option_text.setFillColor(Color::White);
    option_text.setOutlineColor(Color::Black);
    option_text.setOutlineThickness(5);
    option_text.setPosition(Vector2f(960,500));
    option_text.setString("OPTION");
    std::cout << text.getLocalBounds().getSize().y << std::endl;
   
    Texture background;
    if (frame)
    {
        background.loadFromFile("menu1.png");

    }
    else
    {
        background.loadFromFile("menu2.png");

    }
    Sprite background_sprite;
    background_sprite.setTexture(background);
    //if (true) window.setPosition(sf::Vector2i(0 + rand() % 25, 0+ rand() % 25));
    window.draw(background_sprite);
    if (option)
    {
        window.draw(option_text);
    }
    else
    {
        window.draw(play_button.bdisplay(Color::Green,Color::Black));
        window.draw(option_button.bdisplay(Color::White,Color::Black));
        window.draw(exit_button.bdisplay(Color::Red,Color::Black));
    }
    window.draw(text);
    std::cout << Mouse::getPosition(window).x << std::endl;
    std::cout << Mouse::getPosition(window).y << std::endl;
    if (active)
    {
        if (play_button.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
        {
            active = false;
        }
        if (option_button.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
        {
            option = true;
        }
        if (exit_button.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
        {
            window.close();
        }
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
