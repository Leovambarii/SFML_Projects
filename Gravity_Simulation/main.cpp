#include "header.hpp"
//  To compile: g++ main.cpp header.cpp  Particle.cpp GravitySource.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
int main() {
    GravityProject project;
    project.run();
    return 0;
}