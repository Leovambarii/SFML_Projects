#include "header.hpp"

// Constructor for MemoryGameProject class
MemoryGameProject::MemoryGameProject() :
    // Initialize window with specified width, height, and title
    mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MEMORY GAME")
{
    // Set the maximum framerate of the window
    mWindow.setFramerateLimit(FPS_LIMIT);
    // Seed the random number generator with the current time
    srand(time(nullptr));
}

// Main simualtion loop
void MemoryGameProject::run() {
    while (mWindow.isOpen()) {
        processEvents(); // Handle input events
        update(); // Update simualtion state
        render(); // Render simualtion graphics
    }
}

// Handle input events
void MemoryGameProject::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) { // Process events in the event queue
        if (event.type == sf::Event::Closed) // If user closes the window
            mWindow.close(); // Close the window
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) // If user presses Esc key
            mWindow.close(); // Close the window
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // If user clicks the left button on mouse
            sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow); // Get mouse position relative to the window

        }
    }
}