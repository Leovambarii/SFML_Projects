#include "header.hpp"

// --- Block ---

// Constructor for Block class
Block::Block(sf::Vector2f size, sf::Color color, float thickness, sf::Vector2f position) :
color(color)
{
    block_shape.setSize(size);
    block_shape.setFillColor(color);
    block_shape.setOutlineColor(sf::Color::Black);
    block_shape.setOutlineThickness(thickness);
    block_shape.setPosition(position);

    active_color = alterColor(color, COLOR_CHANGE_FACTOR);
}

// Renders the Block object to a given RenderWindow object
void Block::render(sf::RenderWindow &window) {
    window.draw(block_shape);
}

// Toggle color to active/inactive
void Block::toggleBlockColor() {
    sf::Color currentColor = block_shape.getFillColor();
    if (currentColor == color) {
        block_shape.setFillColor(active_color);
        sf::Color active_color = block_shape.getFillColor();
        float r = static_cast<float>(active_color.r);
        float g = static_cast<float>(active_color.g);
        float b = static_cast<float>(active_color.b);
        std::cout << "active color:" << ' ' << r << ' '<< g << ' ' << b << std::endl;
    }
    else if (currentColor == active_color) {
        block_shape.setFillColor(color);
        sf::Color inactive_color = block_shape.getFillColor();
        float r = static_cast<float>(inactive_color.r);
        float g = static_cast<float>(inactive_color.g);
        float b = static_cast<float>(inactive_color.b);
        std::cout << "normal color:" << ' ' << r << ' '<< g << ' ' << b << std::endl;
    }
}

// Function for creating a similar color with altered brightness
sf::Color Block::alterColor(sf::Color color, float factor) {
    // Get the RGB values of the color
    float red = static_cast<float>(color.r);
    float green = static_cast<float>(color.g);
    float blue = static_cast<float>(color.b);

    // Change brightness of each RGB component
    red /= factor;
    green /= factor;
    blue /= factor;

    // Clamp the values to ensure they are between 0 and 255
    red = std::min(std::max(red, 0.0f), 255.0f);
    green = std::min(std::max(green, 0.0f), 255.0f);
    blue = std::min(std::max(blue, 0.0f), 255.0f);

    // Return the new color with the updated RGB values
    return sf::Color(static_cast<sf::Uint8>(red), static_cast<sf::Uint8>(green), static_cast<sf::Uint8>(blue), color.a);
}

// --- MemoryGameProject ---

// Constructor for MemoryGameProject class
MemoryGameProject::MemoryGameProject() :
    // Initialize window with specified width, height, and title
    mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MEMORY GAME", sf::Style::Titlebar | sf::Style::Close),
    current_level(1),
    step_idx(0),
    display_path(true)
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

    // Create four Block objects
    createBlocks();

    // Generate all steps for the game
    createStepsPath();

    for (auto &x : mSteps)
        std::cout << x << " ";
    std::cout << std::endl;
}

// Main simualtion loop
void MemoryGameProject::run() {
    while (mWindow.isOpen()) {
        renderPath(); // Update game state and render graphics
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
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !display_path) { // If user clicks the left button on mouse
            sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow); // Get mouse position relative to the window
            int clickedBlock = checkClick(mousePosition); // Check what block was clicked
            // Check whether correct block was clicked
            if (isCorrectBlock(clickedBlock))
                step_idx++;
            else {
                std::cout << "Incorrect!" << std::endl;
                mWindow.close();
            }
        }
    }
}

// Update game state and render graphics
void MemoryGameProject::renderPath() {
    if (display_path) {
        for (int i=0; i<current_level; i++)
            renderStep(i);
        display_path = !display_path;
        std::cout << "Now repeat!" << std::endl;
    } else {
        // renderBlocks();
        if (step_idx >= current_level) {
            display_path = !display_path;
            step_idx = 0;
            current_level++;
            if (current_level == LEVELS_AMOUNT) {
                std::cout << "-----+++ CONGRATULATIONS! YOU WIN! +++-----" << std::endl;
                mWindow.close();
            }
        } else
            processEvents();
    }
}

// Render game step
void MemoryGameProject::renderStep(int step) {
    mWindow.clear();
    mBlocks[mSteps[step]].toggleBlockColor();
    for (Block& b : mBlocks)
        b.render(mWindow);
    mWindow.display();
    // Pause for given time before rendering the next frame during path display
    sf::sleep(sf::seconds(PAUSE_TIME));
    mWindow.clear();
    mBlocks[mSteps[step]].toggleBlockColor();
    for (Block& b : mBlocks)
        b.render(mWindow);
    mWindow.display();
    sf::sleep(sf::seconds(0.2f));
}

// Create four Block objects
void MemoryGameProject::createBlocks() {
    float a = BLOCK_WIDTH - OUTLINE_THICKNESS;
    float b = BLOCK_HEIGHT - OUTLINE_THICKNESS;

    // Top left block
    mBlocks.push_back(Block(sf::Vector2f(a, b), sf::Color::Green, OUTLINE_THICKNESS, sf::Vector2f(OUTLINE_THICKNESS, OUTLINE_THICKNESS)));
    // Top right block
    mBlocks.push_back(Block(sf::Vector2f(a, b), sf::Color::Red, OUTLINE_THICKNESS, sf::Vector2f(a+OUTLINE_THICKNESS, OUTLINE_THICKNESS)));
    // Bottom left block
    mBlocks.push_back(Block(sf::Vector2f(a-OUTLINE_THICKNESS, b-OUTLINE_THICKNESS), sf::Color::Yellow, OUTLINE_THICKNESS, sf::Vector2f(OUTLINE_THICKNESS, b+2*OUTLINE_THICKNESS)));
    // Bottom right block
    mBlocks.push_back(Block(sf::Vector2f(a, b-OUTLINE_THICKNESS), sf::Color::Blue, OUTLINE_THICKNESS, sf::Vector2f(a+OUTLINE_THICKNESS, b+2*OUTLINE_THICKNESS)));
}

// Add another step to current game
void MemoryGameProject::createStepsPath() {
    for (int i=0; i<LEVELS_AMOUNT; i++)
        mSteps.push_back(rand() % mBlocks.size());
}

// Check what block was clicked
int MemoryGameProject::checkClick(sf::Vector2i mousePosition) {
    int x = mousePosition.x;
    int y = mousePosition.y;
    if (x < BLOCK_WIDTH && y < BLOCK_HEIGHT)
        return 0;
    else if (x >= BLOCK_WIDTH && y < BLOCK_HEIGHT)
        return 1;
    else if (x < BLOCK_WIDTH && y >= BLOCK_HEIGHT)
        return 2;
    else
        return 3;
}

// Check if correct block was clicked
bool MemoryGameProject::isCorrectBlock(int clickedBlock) {
    if (clickedBlock == mSteps[step_idx])
        return true;
    else
        return false;
}

