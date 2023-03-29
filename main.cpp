#include <SFML/Graphics.hpp>
#include "GravitySource.h"
#include "Particle.h"

// To compile: g++ main.cpp GravitySource.cpp Particle.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "My program");    // Window initialization
    window.setFramerateLimit(60);

    GravitySource source(800, 500, 7000);
    Particle particle_1(600, 700, 6, 0);
    Particle particle_2(800, 300, 4, 0);

    while (window.isOpen()) {   // Loop with open window
        sf::Event event;    // Initializing event object
        while (window.pollEvent(event)) {
            if ( event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear(); // Clearing the window

        particle_1.update_physics(source);
        particle_2.update_physics(source);

        source.render(window);

        particle_1.render(window);
        particle_2.render(window);

        window.display();   // Display
    }

    return 0;
}