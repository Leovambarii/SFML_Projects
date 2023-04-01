#ifndef GRAVITY_SOURCE_H
#define GRAVITY_SOURCE_H

#include <SFML/Graphics.hpp>

class GravitySource {
private:
    sf::Vector2f position;
    float strength;
    sf::CircleShape source;

public:
    GravitySource(float pos_x, float pos_y, float strength);

    void render(sf::RenderWindow& window);

    sf::Vector2f get_pos();

    float get_strength();

};

#endif