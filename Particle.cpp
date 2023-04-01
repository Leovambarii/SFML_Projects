#include "Particle.hpp"

Particle::Particle(float pos_x, float pos_y, float velocity_x, float velocity_y, sf::Color color) {
    position.x = pos_x;
    position.y = pos_y;

    velocity.x = velocity_x;
    velocity.y = velocity_y;

    particle_color = color;

    particle_shape.setPosition(position);
    particle_shape.setFillColor(color);
    particle_shape.setRadius(2);
}

void Particle::render(sf::RenderWindow& window) {
        particle_shape.setPosition(position);
        window.draw(particle_shape);
    }

void Particle::update_physics(GravitySource &source) {
    float distance_x = source.get_pos().x - position.x;
    float distance_y = source.get_pos().y - position.y;

    float distance = sqrt(distance_x*distance_x + distance_y*distance_y);

    float distance_inv = 1.f / distance;    // Inversing the distance

    float normalized_x = distance_inv * distance_x; // Normalizing the distance for x
    float normalized_y = distance_inv * distance_y; // Normalizing the distance for y

    float inverse_square_dropoff = distance_inv * distance_inv; // Calculating the dropoff gravity from distance

    float acceleration_x = normalized_x * source.get_strength() * inverse_square_dropoff;
    float acceleration_y = normalized_y * source.get_strength() * inverse_square_dropoff;

    velocity.x += acceleration_x;
    velocity.y += acceleration_y;

    position.x += velocity.x;
    position.y += velocity.y;
}
