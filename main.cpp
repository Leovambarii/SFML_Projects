// #include <SFML/Graphics.hpp>
#include "GravitySource.h"
#include "Particle.h"
#include <vector>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

#define SEED 5
#define FPS_LIMIT 60
// To compile: g++ main.cpp Particle.cpp GravitySource.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system

int main() {
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "GRAVITY PROJECT");    // Window initialization
    window.setFramerateLimit(FPS_LIMIT);    // Settinf fps limit

    srand(time(nullptr)); // Creating seed for random generator

    GravitySource source(800, 500, 7000);   // Creating gravity source

    std::vector<Particle> particles;    // Vector for storing particles

    bool pause = false;
    // TODO colisions
    // TODO movement trace
    // TODO deletion of particle on hit with the source

    while (window.isOpen()) {   // Loop with open window
        sf::Event event;    // Initializing event object
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)    // Closing window event
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {   // Closing window event
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {  // Pausing the simulation
                pause = !pause;
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {  // Clearing particles
                particles.clear();
            } else if (event.type == sf::Event::MouseButtonPressed) {   // Adding particle with a mouse event
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Color color = sf::Color(rand()%256, rand()%256, rand()%256);
                sf::Vector2f velocity(rand()%5, rand()%5);
                if (event.mouseButton.button == sf::Mouse::Left) {  // Adding single particle
                    particles.push_back(Particle(mousePosition.x, mousePosition.y, velocity.x, velocity.y, color));
                } else if (event.mouseButton.button == sf::Mouse::Right) {  // Adding multiple particles
                    particles.push_back(Particle(mousePosition.x, mousePosition.y, velocity.x, velocity.y, color));
                    particles.push_back(Particle(mousePosition.x+rand()%15+1, mousePosition.y+rand()%15+1, velocity.x, velocity.y, color));
                    particles.push_back(Particle(mousePosition.x+rand()%15+1, mousePosition.y-rand()%15+1, velocity.x, velocity.y, color));
                    particles.push_back(Particle(mousePosition.x-rand()%15+1, mousePosition.y+rand()%15+1, velocity.x, velocity.y, color));
                    particles.push_back(Particle(mousePosition.x-rand()%15+1, mousePosition.y-rand()%15+1, velocity.x, velocity.y, color));
                }
            }
        }

        window.clear(); // Clearing the window

        if (!pause) {   // Updating particle physics when simulation is not paused
            for (Particle& p : particles)
                p.update_physics(source);
        }
        source.render(window);  // Rendering the source

        for (Particle p : particles)    // Rendering particles
            p.render(window);

        window.display();   // Display
    }

    return 0;
}