#include <SFML/Graphics.hpp>
#include "GravitySource.h"
#include "Particle.h"
#include <vector>
#include <cstdlib>

#define SEED 5
// To compile: g++ main.cpp GravitySource.cpp Particle.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "GRAVITY PROJECT");    // Window initialization
    window.setFramerateLimit(60);

    GravitySource source(800, 500, 7000);

    std::vector<Particle> particles;
    particles.push_back(Particle(600, 700, 6, 0));
    particles.push_back(Particle(800, 300, 4, 0));
    for (int i=0; i<5; i++) {
        particles.push_back(Particle(rand() % 1500, rand() % 900, rand()%5+1, rand()%5));
    }

    bool pause = false;
    bool spacePressed = false;

    while (window.isOpen()) {   // Loop with open window
        sf::Event event;    // Initializing event object
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !spacePressed) {
                spacePressed = true;
                pause = !pause;
            } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
                spacePressed = false;
        }


        window.clear(); // Clearing the window

        if (!pause) {
            for (Particle& p : particles)
                p.update_physics(source);
        }
        source.render(window);

        for (Particle p : particles)
            p.render(window);

        window.display();   // Display
    }

    return 0;
}