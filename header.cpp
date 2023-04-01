#include "header.hpp"

GravityProject::GravityProject() :
    mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GRAVITY PROJECT"),
    mSource(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 7000),
    mPaused(false)
{
    mWindow.setFramerateLimit(FPS_LIMIT);
    srand(time(nullptr));
}

void GravityProject::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GravityProject::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            mWindow.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            mPaused = !mPaused;
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
            mParticles.clear();
        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
            sf::Color color = sf::Color(rand()%256, rand()%256, rand()%256);
            sf::Vector2f velocity(rand()%5, rand()%5);
            if (event.mouseButton.button == sf::Mouse::Left)
                mParticles.push_back(Particle(mousePosition.x, mousePosition.y, velocity.x, velocity.y, color));
            else if (event.mouseButton.button == sf::Mouse::Right) {
                mParticles.push_back(Particle(mousePosition.x, mousePosition.y, velocity.x, velocity.y, color));
                mParticles.push_back(Particle(mousePosition.x+rand()%15+1, mousePosition.y+rand()%15+1, velocity.x, velocity.y, color));
                mParticles.push_back(Particle(mousePosition.x+rand()%15+1, mousePosition.y-rand()%15+1, velocity.x, velocity.y, color));
                mParticles.push_back(Particle(mousePosition.x-rand()%15+1, mousePosition.y+rand()%15+1, velocity.x, velocity.y, color));
                mParticles.push_back(Particle(mousePosition.x-rand()%15+1, mousePosition.y-rand()%15+1, velocity.x, velocity.y, color));
            }
        }
    }
}

void GravityProject::update() {
    if (!mPaused) {
        for (Particle& p : mParticles)
            p.update_physics(mSource);
    }
}

void GravityProject::render() {
    mWindow.clear();
    mSource.render(mWindow);
    for (Particle p : mParticles)
        p.render(mWindow);
    mWindow.display();
}