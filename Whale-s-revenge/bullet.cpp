#include "bullet.h"
void bullet::init(int x, int y)
{
    shape.setPosition(x, y);
}


sf::Vector2f bullet::normalize(const sf::Vector2f& vector)
{
    // Calcul de la norme
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    // Si la norme est proche de zéro, retourner un vecteur nul
    if (length == 0.0f)
        return sf::Vector2f(0.0f, 0.0f);

    // Diviser chaque composante par la norme
    return sf::Vector2f((vector.x / length), (vector.y / length));
}

void bullet::update(float speed)
{
    shape.move(normalize(player_pos - ennemy_pos)*speed);
}
