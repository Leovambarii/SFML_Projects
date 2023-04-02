// This is the Particle class implementation file

#include "Particle.hpp"

// Constructor for creating a new Particle object with specified position, velocity, and color
Particle::Particle(float pos_x, float pos_y, float velocity_x, float velocity_y, sf::Color color, float radius) {
    position.x = pos_x;
    position.y = pos_y;
    velocity.x = velocity_x;
    velocity.y = velocity_y;
    particle_color = color;
    particle_radius = radius;
    particle_shape.setPosition(position);
    particle_shape.setFillColor(color);
    particle_shape.setRadius(particle_radius);
}

// Renders the Particle object to a given RenderWindow object
    void Particle::render(sf::RenderWindow &window) {
    particle_shape.setPosition(position);
    window.draw(particle_shape);
    draw_particle_trajectory(window);
}

// Updates the Particle object's physics based on the gravitational influence of a GravitySource object
void Particle::update_physics(GravitySource &source) {
    float distance_x = source.get_pos().x - position.x;
    float distance_y = source.get_pos().y - position.y;

    float distance = sqrt(distance_x*distance_x + distance_y*distance_y); // Calculating distance between particle and source

    float distance_inv = 1.f / distance; // Inversing the distance to avoid dividing by zero

    float normalized_x = distance_inv * distance_x; // Normalizing the distance for x
    float normalized_y = distance_inv * distance_y; // Normalizing the distance for y

    float inverse_square_dropoff = distance_inv * distance_inv; // Calculating the dropoff gravity from distance

    float acceleration_x = normalized_x * source.get_strength() * inverse_square_dropoff; // Calculating acceleration for x
    float acceleration_y = normalized_y * source.get_strength() * inverse_square_dropoff; // Calculating acceleration for y

    velocity.x += acceleration_x; // Updating the velocity for x
    velocity.y += acceleration_y; // Updating the velocity for y

    position += velocity; // Updating the position

    trajectory_trace.push_back(position); // Add new postion to the trajectory trace vector
}

// Method that returns the postion vector of the particle
sf::Vector2f Particle::get_pos() {
    return position;
}

// Method that returns the velocity vector of the particle
sf::Vector2f Particle::get_velocity() {
    return velocity;
}

// Method that returns the radius of the particle
float Particle::get_radius() {
    return particle_radius;
}

// Check whether given Particle position is inside the GravitySource
bool Particle::check_source_collision(GravitySource &source) {
    float distance_x = source.get_pos().x - position.x;
    float distance_y = source.get_pos().y - position.y;

    float source_radius = source.get_radius();

    float distance = sqrt(distance_x*distance_x + distance_y*distance_y); // Calculating distance between particle and source

    return distance <= source_radius*1.5f;
}

// Draw the trajectory trace
void Particle::draw_particle_trajectory(sf::RenderWindow& window) {
    // Only keep the last 5 and current position in the trajectory trace vector
    while (trajectory_trace.size() > TRACE_SIZE) {
        trajectory_trace.erase(trajectory_trace.begin());
    }

    if (trajectory_trace.size() > 3) {
        // Draw lines connecting the points in the trajectory trace vector
        for (size_t i=0; i < trajectory_trace.size()-2; i++) {
            sf::Vertex line[] = {
                sf::Vertex(trajectory_trace[i], particle_color),
                sf::Vertex(trajectory_trace[i + 1], particle_color)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}