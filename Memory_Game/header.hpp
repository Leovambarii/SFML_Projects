#ifndef HEADER_HPP
#define HEADER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define FPS_LIMIT 60 // Frames per second limit
#define WINDOW_WIDTH 700 // Width of the simulation window
#define WINDOW_HEIGHT 700 // Height of the simulation window
#define BLOCK_WIDTH WINDOW_WIDTH/2 // Width of the block
#define BLOCK_HEIGHT WINDOW_HEIGHT/2 // Height of the block
#define OUTLINE_THICKNESS 5 // Thickness of outlines between rectangles
#define SCORE_RADIUS WINDOW_WIDTH*0.10  // Radius of circle behind score
#define COLOR_CHANGE_FACTOR 3.0 // Factor of color being darker when it is active
#define PAUSE_TIME 1.0f // Amount of seconds to wait between showing each step path
#define LEVELS_AMOUNT 100 // Maximum amout of steps in generated path

class Block {
public:
    Block(sf::Vector2f size, sf::Color color, float thickness, sf::Vector2f position);
    void render(sf::RenderWindow& window);
    void toggleBlockColor();

private:
    sf::RectangleShape block_shape;
    sf::Color active_color;
    sf::Color color;

    sf::Color alterColor(sf::Color color, float factor);
};

class MemoryGameProject {
public:
    MemoryGameProject();
    void run();
private:
    unsigned int current_level;
    unsigned int step_idx;
    bool display_path;

    void processEvents();
    void renderPath();
    void renderStep(int step);
    void createBlocks();
    void createStepsPath();
    int checkClick(sf::Vector2i mousePosition);
    bool isCorrectBlock(int clickedBlock);

    // Targeted window for drawing elements
    sf::RenderWindow mWindow;

    // Vector that is storing blocks order
    std::vector<int> mSteps;

    // Vector that is storing blocks
    std::vector<Block> mBlocks;
};

#endif