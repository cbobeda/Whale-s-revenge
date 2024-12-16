#include "Main menu.h"

button selectmenu_button(100, 300, 300, 100, false);
button option_button(100, 500, 300, 100, false);
button option_exit_button(100, 200, 100, 100, false);
button exit_button(100, 700, 300, 100, false);
button easy(500, 300, 100, 100, true);
button medium(500, 500, 100, 100, true);
button hard(500, 700, 100, 100, true);

button CampagneButton(600, 650, 250, 175, false);
button CustomLevelButton(1200, 650, 250, 175, false);

button AddMelee(400, 135, 50, 100, true);
button RemoveMelee(100, 135, 50, 100, true);
button nbMelee(200, 135, 150, 100, true);

button AddDistance(400, 285, 50, 100, true);
button RemoveDistance(100, 285, 50, 100, true);
button nbDistance(200, 285, 150, 100, true);

button PlayCustom(1580, 950, 300, 100, false);

bool active = true;
bool frame = false;
bool isready = false;
bool option = false;
bool bcd = true;

Clock watch;
float frameDuration = 0.5f; // Durée d'une frame (en secondes)

sf::Clock buttonCd;
float bframeDuration = 0.5f; // Durée d'une frame (en secondes)


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


bool Main_menu::mdisplay(RenderWindow& window, Event event)
{
    Font font;
    font.loadFromFile("font/MinecraftStandard.otf");
    Text text;
    text.setFont(font);
    text.setString("Whale's revenge");
    text.setCharacterSize(40);
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(5);
    text.setOrigin(262, 26.5);
    text.setPosition(Vector2f(960, 200));
    text.setScale(1.5, 1.5);


    Text option_text2;
    option_text2.setFont(font);
    option_text2.setCharacterSize(40);
    option_text2.setFillColor(Color::White);
    option_text2.setOutlineColor(Color::Black);
    option_text2.setOutlineThickness(5);
    sf::FloatRect option_text2rect = option_text2.getGlobalBounds();
    option_text2.setOrigin(Vector2f(option_text2rect.left + option_text2rect.width / 2, option_text2rect.top + option_text2rect.height / 2));
    option_text2.setPosition(Vector2f(window.getSize().x / 2, 300));
    option_text2.setScale(1.5, 1.5);
    option_text2.setString("OPTION");

    Texture background;
    if (frame)
    {
        background.loadFromFile("assets/menu1.png");

    }
    else
    {
        background.loadFromFile("assets/menu2.png");

    }
    Sprite background_sprite;
    background_sprite.setTexture(background);
    if (true)window.setPosition(sf::Vector2i(0 + rand() % 25, 0 + rand() % 25));
    window.draw(background_sprite);
    if (option)
    {
        
        window.draw(option_text2);
        option_exit_button.bdisplay(Color::Red, Color::Black, window, 20, "");
        easy.bdisplay(Color::Yellow, Color::Black, window, 10, "EASY");
        if (easy.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left) && bcd)
        {
            easy.setclicked();
            medium.setclicked(true);
            hard.setclicked(true);
            bcd = false;
            DifficultyIndex = 1;
        }
        medium.bdisplay(Color::Yellow, Color::Black, window, 10, "MEDIUM");
        if (medium.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left) && bcd)
        {
            medium.setclicked();
            easy.setclicked(true);
            hard.setclicked(true);
            bcd = false;
            DifficultyIndex = 2;
        }
        hard.bdisplay(Color::Yellow, Color::Black, window, 10, "HARD");
        if (hard.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left) && bcd)
        {
            hard.setclicked();
            medium.setclicked(true);
            easy.setclicked(true);
            bcd = false;
            DifficultyIndex = 3;
        }
        if (option_exit_button.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
        {
            option = false;
        }
    }
    else
    {
        //Pour display
        switch (menuindex) {
        case MainMenu:
            selectmenu_button.bdisplay(Color::Green, Color::Black, window, 20, "PLAY");
            option_button.bdisplay(Color::Blue, Color::Black, window, 20, "OPTION");
            exit_button.bdisplay(Color::Red, Color::Black, window, 20, "EXIT");
            break;
        case LevelMenu:
            CampagneButton.bdisplay(Color(252, 186, 3), Color::Black, window, 20, "Campagne");
            CustomLevelButton.bdisplay(Color(252, 186, 3), Color::Black, window, 20, "Custom");
            break;
        case CustomMenu:
            AddMelee.bdisplay(Color(6, 117, 43), Color::Black, window, 20, "+");
            RemoveMelee.bdisplay(Color(117, 6, 21), Color::Black, window, 20, "-");
            nbMelee.bdisplay(Color(222, 240, 250), Color::Black, window, 20, "");

            AddDistance.bdisplay(Color(6, 117, 43), Color::Black, window, 20, "+");
            RemoveDistance.bdisplay(Color(117, 6, 21), Color::Black, window, 20, "-");
            nbDistance.bdisplay(Color(222, 240, 250), Color::Black, window, 20, "");

            PlayCustom.bdisplay(Color::Green, Color::Black, window, 20, "PLAY");
            break;
        }

    }
    window.draw(text);
    // Pour les collisions
    if (active)
    {
        switch (menuindex) {
        case MainMenu:
            if (selectmenu_button.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                menuindex = LevelMenu;
            }
            if (option_button.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                option = true;
            }
            if (exit_button.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                window.close();
            }
            break;
        case LevelMenu:
            if (CampagneButton.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                active = false;
            }
            if (CustomLevelButton.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                menuindex = CustomMenu;
            }
            break;
        case CustomMenu:
            if (AddMelee.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                nbMeleeEnnemy += 1;
                std::cout << nbMeleeEnnemy << std::endl;
            }
            if (AddDistance.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                nbDistanceEnnemy += 1;
                std::cout << nbDistanceEnnemy << std::endl;
            }
            if (PlayCustom.check(Mouse::getPosition().x, Mouse::getPosition().y, window) && Mouse::isButtonPressed(Mouse::Left))
            {
                sharks.CreateShark(nbMeleeEnnemy, nbDistanceEnnemy, 4, 2);
                isPlayingCustom = true;
                active = false;
            }
            break;

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
    if (buttonCd.getElapsedTime().asSeconds() > bframeDuration)
    {
        bcd = true;
        buttonCd.restart();
    }

    return active;
}
