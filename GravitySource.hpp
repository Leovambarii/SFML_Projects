#ifndef GRAVITY_SOURCE_HPP
#define GRAVITY_SOURCE_HPP

#include <SFML/Graphics.hpp>

class GravitySource {
private:
    sf::Vector2f position;
    float source_strength;
    float source_radius;
    sf::CircleShape source;

public:
    GravitySource(float pos_x, float pos_y, float strength, float radius);

    void render(sf::RenderWindow& window);

    sf::Vector2f get_pos();

    float get_strength();

    float get_radius();

};

#endif