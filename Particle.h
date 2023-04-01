#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include "GravitySource.h"

class Particle {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color particle_color;
    sf::CircleShape particle_shape;

public:
    Particle(float pos_x, float pos_y, float velocity_x, float velocity_y, sf::Color color);

    void render(sf::RenderWindow& window);

    sf::Vector2f get_pos();

    void update_physics(GravitySource &source);

};

#endif