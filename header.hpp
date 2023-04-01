#ifndef HEADER_HPP
#define HEADER_HPP

#include <SFML/Graphics.hpp>
#include "GravitySource.hpp"
#include "Particle.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

#define SEED 5
#define FPS_LIMIT 60
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1000

class GravityProject {
public:
    GravityProject();
    void run();
private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow mWindow;
    GravitySource mSource;
    std::vector<Particle> mParticles;
    bool mPaused;
};

#endif