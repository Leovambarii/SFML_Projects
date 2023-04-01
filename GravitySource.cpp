#include "GravitySource.hpp"

GravitySource::GravitySource(float pos_x, float pos_y, float strength) {
    position.x = pos_x;
    position.y = pos_y;
    this->strength = strength;

    source.setPosition(position);
    source.setFillColor(sf::Color::Yellow);
    source.setRadius(10);
}

void GravitySource::render(sf::RenderWindow& window) {
    window.draw(source);
}

sf::Vector2f GravitySource::get_pos() {
    return position;
}

float GravitySource::get_strength() {
    return strength;
}