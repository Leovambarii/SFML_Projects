#include "header.hpp"

// Constructor for MemoryGameProject class
MemoryGameProject::MemoryGameProject() :
    // Initialize window with specified width, height, and title
    mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MEMORY GAME", sf::Style::Titlebar | sf::Style::Close)
{
    // Set the maximum framerate of the window
    mWindow.setFramerateLimit(FPS_LIMIT);
    // get the screen resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // calculate the center position of the screen
    int centerX = (desktop.width - mWindow.getSize().x) / 2;
    int centerY = (desktop.height - mWindow.getSize().y) / 2;

    // set the position of the window to the center of the screen
    mWindow.setPosition(sf::Vector2i(centerX, centerY));

    // Seed the random number generator with the current time
    srand(time(nullptr));
}

// Main simualtion loop
void MemoryGameProject::run() {
    while (mWindow.isOpen()) {
        processEvents(); // Handle input events
        // update(); // Update simualtion state
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

void MemoryGameProject::render() {  // TODO Create separate class for blocks to ease rendering and atributes changing
    mWindow.clear();

    float a = WINDOW_WIDTH/2 - OUTLINE_THICKNESS;
    float b = WINDOW_HEIGHT/2 - OUTLINE_THICKNESS;

    sf::RectangleShape rectangle_top_left;
    rectangle_top_left.setSize(sf::Vector2f(a, b));
    rectangle_top_left.setFillColor(sf::Color::Green);
    rectangle_top_left.setOutlineColor(sf::Color::Black);
    rectangle_top_left.setOutlineThickness(OUTLINE_THICKNESS);
    rectangle_top_left.setPosition(OUTLINE_THICKNESS, OUTLINE_THICKNESS);
    mWindow.draw(rectangle_top_left);

    sf::RectangleShape rectangle_top_right;
    rectangle_top_right.setSize(sf::Vector2f(a, b));
    rectangle_top_right.setFillColor(sf::Color::Red);
    rectangle_top_right.setOutlineColor(sf::Color::Black);
    rectangle_top_right.setOutlineThickness(OUTLINE_THICKNESS);
    rectangle_top_right.setPosition(a+OUTLINE_THICKNESS, OUTLINE_THICKNESS);
    mWindow.draw(rectangle_top_right);

    sf::RectangleShape rectangle_bottom_left;
    rectangle_bottom_left.setSize(sf::Vector2f(a-OUTLINE_THICKNESS, b-OUTLINE_THICKNESS));
    rectangle_bottom_left.setFillColor(sf::Color::Yellow);
    rectangle_bottom_left.setOutlineColor(sf::Color::Black);
    rectangle_bottom_left.setOutlineThickness(OUTLINE_THICKNESS);
    rectangle_bottom_left.setPosition(OUTLINE_THICKNESS, b+OUTLINE_THICKNESS*2);
    mWindow.draw(rectangle_bottom_left);

    sf::RectangleShape rectangle_bottom_right;
    rectangle_bottom_right.setSize(sf::Vector2f(a, b-OUTLINE_THICKNESS));
    rectangle_bottom_right.setFillColor(sf::Color::Blue);
    rectangle_bottom_right.setOutlineColor(sf::Color::Black);
    rectangle_bottom_right.setOutlineThickness(OUTLINE_THICKNESS);
    rectangle_bottom_right.setPosition(a+OUTLINE_THICKNESS, b+OUTLINE_THICKNESS*2);
    mWindow.draw(rectangle_bottom_right);

    sf::CircleShape score;
    score.setRadius(SCORE_RADIUS);
    score.setFillColor(sf::Color::White);
    score.setOutlineColor(sf::Color::Black);
    score.setOutlineThickness(OUTLINE_THICKNESS);
    score.setPosition(a-SCORE_RADIUS, b-SCORE_RADIUS);
    mWindow.draw(score);

    mWindow.display();
}