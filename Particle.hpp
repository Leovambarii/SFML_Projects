#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <math.h>
#include "GravitySource.hpp"

class Particle {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color particle_color;
    float particle_radius;
    sf::CircleShape particle_shape;

public:
    Particle(float pos_x, float pos_y, float velocity_x, float velocity_y, sf::Color color, float radius);

    void render(sf::RenderWindow& window);

    sf::Vector2f get_pos();

    sf::Vector2f get_velocity();

    float get_radius();

    void update_physics(GravitySource &source);

    bool check_source_collision(GravitySource &source);

};

#endif