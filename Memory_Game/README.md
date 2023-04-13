# `Simon Game Project`

This project is a simple implementation of the popular Simon game, which involves memorizing and repeating a sequence of colors and sounds. The game is built using C++ and the SFML graphics library.

This project was created to remind myself object-oriented programming in C++.


## `Getting Started:`
1. To run this project, you will need to have the SFML library installed on your system. You can download it from the [SFML website](https://www.sfml-dev.org/download.php).

2. Once you have installed SFML, you can compile the project using C++ compiler. Here's an example using g++:
    ```
    g++ main.cpp header.cpp -o simon_game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```

3. Then run this command:
    ```
    ./simon_game
    ```
This will compile and run the project, and you should see the Simon game screen appear on the middle of your screen.

## `How to Play:`
The Simon game consists of four colored blocks (red, green, blue, and yellow) and a score counter. The game randomly generates a sequence of colors and sounds that the player must memorize and repeat. The length of the sequence increases with each level of the game.

To start the game, simply press SPACE. The game will begin by displaying a sequence of colors and sounds that you must memorize. Once the sequence is complete, the score circle will turn white, and you must click on the blocks in the same order that they were displayed. If you click on the wrong block or if you click during sequance display, the game will end and close.

## `Project Structure:`
The project consists of the following files:
- `main.cpp`: This is the main file of the project that runs the game.

- `header.hpp`: This file contains the class definitions and function declarations used in the project.

- `header.cpp`: This file contains the class and functions implementation.

- `Sounds`: This folder contains the sound files used in the project.

- `Fonts`: This folder contains the font files used in the project.

## `Class Definitions:`
## `Block Class`
This class represents a block object in the game. The Block class is responsible for creating, rendering, and modifying a block object which is represented as a rectangle shape.

## `Score Class`
This class represents a score object in the game. The Score class is responsible for creating, rendering, and modifying a score object which is represented as a circle shape with text.

## `MemoryGameProject Class`
This class is responsible for handling the game mechanics and UI. It initializes the game and runs it. It keeps track of the current step index, whether to display the block path or not, and the current score. It also contains various methods for processing user input, rendering the game screen, and handling the game logic.

## `Acknowledgments`
This project is inspired by the classic Simon game, which was created by Ralph H. Baer and Howard J. Morrison in 1978.