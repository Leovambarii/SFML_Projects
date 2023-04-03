#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <math.h>
#include "GravitySource.hpp"

#define TRACE_SIZE 100
#define TRACE true

class Particle {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color particle_color;
    float particle_radius;
    sf::CircleShape particle_shape;
    std::vector<sf::Vector2f> trajectory_trace;

public:
    Particle(float pos_x, float pos_y, float velocity_x, float velocity_y, sf::Color color, float radius);

    void render(sf::RenderWindow& window);

    sf::Vector2f get_pos();

    sf::Vector2f get_velocity();

    float get_radius();

    void update_physics(GravitySource &source);

    bool check_source_collision(GravitySource &source);

    void draw_particle_trajectory(sf::RenderWindow &window);

    sf::Vector2f get_catmull_rom_point(float t, const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4);
};

#endif