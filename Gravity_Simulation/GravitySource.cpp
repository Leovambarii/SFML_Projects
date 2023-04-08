// This is the GravitySource class implementation file

#include "GravitySource.hpp"

// Constructor for creating a new GravitySource object with specified position and strength
GravitySource::GravitySource(float pos_x, float pos_y, float strength, float radius) {
    // Set the position of the gravity source using the given x and y coordinates
    position.x = pos_x;
    position.y = pos_y;
    // Set the strength of the gravity source using the given value
    source_strength = strength;

    // Set the radius of the gravity source
    source_radius = radius;

    // Initialize a circular shape object representing the gravity source
    source.setPosition(position);
    source.setFillColor(sf::Color::Yellow);
    source.setRadius(source_radius);
}

// Method that draws the gravity source onto the given window
void GravitySource::render(sf::RenderWindow& window) {
    window.draw(source);
}

// Method that returns the position vector of the gravity source
sf::Vector2f GravitySource::get_pos() {
    return position;
}

// Method that returns the strength of the gravity source
float GravitySource::get_strength() {
    return source_strength;
}

// Method that returns the radius of the gravity source
float GravitySource::get_radius() {
    return source_radius;
}