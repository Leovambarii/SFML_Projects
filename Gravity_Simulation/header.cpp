#include "header.hpp"

// Constructor for the GravityProject class
GravityProject::GravityProject() :
    // Initialize window with specified width, height, and title
    mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GRAVITY PROJECT"),
    // Set paused state to false initially
    mPaused(false)
{
    // Set the maximum framerate of the window
    mWindow.setFramerateLimit(FPS_LIMIT);
    // Seed the random number generator with the current time
    srand(time(nullptr));
}

// Main simualtion loop
void GravityProject::run() {
    while (mWindow.isOpen()) {
        processEvents(); // Handle input events
        update(); // Update simualtion state
        check_collisions(); // Check for particle colisions with the gravity source
        render(); // Render simualtion graphics
    }
}

// Handle input events
void GravityProject::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) { // Process events in the event queue
        if (event.type == sf::Event::Closed) // If user closes the window
            mWindow.close(); // Close the window
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) // If user presses Esc key
            mWindow.close(); // Close the window
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) // If user presses Space key
            mPaused = !mPaused; // Toggle paused state
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) // If user presses C key
            mParticles.clear(); // Clear all particles
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V) { // If user presses V key
            mGravitySources.clear(); // Clear all gravity sources
        } else if (event.type == sf::Event::MouseButtonPressed) { // If user clicks the mouse
            sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow); // Get mouse position relative to the window
            if (event.mouseButton.button == sf::Mouse::Left) { // If user clicks the left mouse button
                sf::Color color = sf::Color(rand()%256, rand()%256, rand()%256); // Generate a random color
                sf::Vector2f velocity(rand()%5, rand()%5); // Generate a random velocity
                // Create multiple new particles at random offsets from the mouse position
                for (int i=0; i<MULTIPLE_PARTICLES_AMOUNT; i++) {
                    mParticles.push_back(Particle(mousePosition.x+rand()%(MULTIPLE_PARTICLES_AMOUNT*PARTICLE_RADIUS+1), mousePosition.y+rand()%(MULTIPLE_PARTICLES_AMOUNT*PARTICLE_RADIUS+1), velocity.x, velocity.y, color, PARTICLE_RADIUS));
                }
            } else if (event.mouseButton.button == sf::Mouse::Right) { // If user clicks the right mouse button
                mGravitySources.push_back(GravitySource(mousePosition.x, mousePosition.y, STRENGTH, SOURCE_RADIUS)); // Creating gravity source on mouse position
            }
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow); // Get mouse position relative to the window
                sf::Color color = sf::Color(rand()%256, rand()%256, rand()%256); // Generate a random color
                sf::Vector2f velocity(rand()%5, rand()%5); // Generate a random velocity
                mParticles.push_back(Particle(mousePosition.x, mousePosition.y, velocity.x, velocity.y, color, PARTICLE_RADIUS)); // Create a new particle at the mouse position
            }
        }
    }
}

// Update simualtion state
void GravityProject::update() {
    // If not paused, update physics for all particles
    if (!mPaused) {
        for (Particle& p : mParticles) {
            for (GravitySource& s : mGravitySources) {
                p.update_physics(s);
            }
        }
    }
}

// Check for particle colisions with the gravity source
void GravityProject::check_collisions() {
    for (auto it = mParticles.begin(); it != mParticles.end();) {
        bool collided = false;
        for (GravitySource& s : mGravitySources)  {
            if (it->check_source_collision(s)) {
                collided = true;
                break;
            }
        }
        if (collided == true) {
            it = mParticles.erase(it);
            continue;
        }
        ++it;
    }
}

// Render simualtion graphics
void GravityProject::render() {
    mWindow.clear();
    for (GravitySource s : mGravitySources) {
        s.render(mWindow);
    }
    for (Particle p : mParticles) {
        p.render(mWindow);
    }
    mWindow.display();
}