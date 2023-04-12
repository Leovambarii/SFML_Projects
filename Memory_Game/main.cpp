#include "header.hpp"
//  To compile: g++ main.cpp header.cpp -o main -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
int main() {
    MemoryGameProject project;
    project.run();
    return 0;
}

// TODO add score
// TODO add correct step by step generation after sucessful level
// TODO add sounds when the given block path is displayed and clicked