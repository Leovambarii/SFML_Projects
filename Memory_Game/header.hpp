#ifndef HEADER_HPP
#define HEADER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

#define SEED 5 // Seed for srand generation
#define FPS_LIMIT 60 // Frames per second limit
#define WINDOW_WIDTH 500 // Width of the simulation window
#define WINDOW_HEIGHT 500 // Height of the simulation window
#define STRENGTH 5000 // Strength of the gravity source

class MemoryGameProject {
public:
    MemoryGameProject();
    void run();
private:
    void processEvents();
    void update();
    void render();

    // Targeted window for drawing elements
    sf::RenderWindow mWindow;

    // Vector that is storing blocks order
    std::vector<int> mBlocks;
};

#endif