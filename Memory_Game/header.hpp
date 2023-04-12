/**

@file header.hpp
@brief Header file for Memory Game project
*/

#ifndef HEADER_HPP
#define HEADER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define FPS_LIMIT 30 // Frames per second limit
#define WINDOW_WIDTH 700 // Width of the simulation window
#define WINDOW_HEIGHT 700 // Height of the simulation window
#define BLOCK_WIDTH WINDOW_WIDTH/2.f // Width of the block
#define BLOCK_HEIGHT WINDOW_HEIGHT/2.f // Height of the block
#define OUTLINE_THICKNESS 5 // Thickness of outlines between rectangles
#define SCORE_RADIUS WINDOW_WIDTH*0.1f  // Radius of circle behind score
#define COLOR_CHANGE_FACTOR 3.0f // Factor of color being darker when it is active
#define PAUSE_TIME 1.0f // Amount of seconds to wait between showing each step path
#define SOUND_PATH_AND_FILE_NAME "Sounds/simonSound" // String that indicates folder that contains sounds and first part of sound files name - files must be named as simonSound0.wav ... simonSound3.wav
#define FONT_PATH "myFonts/arial.ttf" // String that indicates path for the font file
#define FONT_SIZE 60 // Character size of the score text

/**
 * @class Block
 * @brief A class that represents a block object.
 * The Block class is responsible for creating, rendering, and modifying a block object which is represented as a rectangle shape.
 */
class Block {
public:
    /**
     * @brief Construct a new Block object
     * @param size The size of the block object shape.
     * @param color The normal color of the block object shape.
     * @param thickness The thickness of the block object shape outline.
     * @param position The position of the block object shape.
     */
    Block(sf::Vector2f size, sf::Color color, float thickness, sf::Vector2f position);

    /**
     * @brief Renders the block object shape onto the specified render window.
     * @param window The render window to render the block object onto.
     */
    void render(sf::RenderWindow& window);

    /**
     * @brief Toggles the color of the block object between its original color and its darker active color.
     */
    void toggleBlockColor();

private:
    sf::RectangleShape block_shape; // The rectangle shape of the block.
    sf::Color active_color; // The active color of the block.
    sf::Color color; // The color of the block.

    /**
     * @brief The function that alters the color of the block.
     * @param color The original color of the block.
     * @param factor The factor of color being darker when it is active.
     * @return sf::Color - The altered color of the block.
     */
    sf::Color alterColor(sf::Color color, float factor);
};

/**
 * @class Score
 * @brief Represents a score object in the game.
 */
class Score {
public:
    /**
     * @brief Constructs a new Score object with the specified radius, thickness and position.
     *
     * @param radius The radius of the score's circular shape.
     * @param thickness The thickness of the score's circular shape outline.
     * @param position The position of the score object shape.
     */
    Score(float radius, float thickness, sf::Vector2f position);

    /**
     * @brief Renders the block object shape and text score onto the specified render window.
     * @param window The render window to render the score object onto.
     */
    void render(sf::RenderWindow& window);

    /**
     * @brief Toggles the color of the score object's depending whether there is currently path rendering or not.
     * This method toggles the color of the score object's render path based on the specified boolean value.
     * @param render_path_state The boolean value to toggle the render path color.
     */
    void toggleScoreColor(bool render_path_state);

    /**
    * @brief Updates the score object's value.
    * This method updates the score object's value based on the current level and other game parameters. It also centers the score text on certain level milestones (10, 100, 1000).
    */
    void updateScore();

    /**
     * @brief Get the position of the Score object shape.
     * @return sf::Vector2f - The position of the score object shape.
     */
    sf::Vector2f getPosition();

    /**
     * @brief Centers the score text on the screen.
     * This method centers the score text on the screen by adjusting its position based on the screen size.
     */
    void centerScore();

    unsigned int current_level;

private:
    sf::CircleShape score_shape;
    sf::Color color;
    sf::Color render_path_color;
    sf::Text scoreText;
    sf::Font scoreFont;
};

/**
 * @brief The MemoryGameProject class is responsible for handling the game mechanics and UI.
 * The class initializes the game and runs it. It keeps track of the current step index,
 * whether to display the block path or not, and the current score. It also contains
 * various methods for processing user input, rendering the game screen, and handling the game logic.
 */
class MemoryGameProject {
public:
    /**
     * @brief Constructs a new MemoryGameProject object.
     * Initializes the step index, display path, and score.
     */
    MemoryGameProject();

    /**
     * @brief Runs the memory game.
     * This method initializes the game window and starts the game loop.
     * It continuously processes events and updates the screen until the game ends.
     */
    void run();

private:
    unsigned int step_idx;
    bool display_path;
    Score score;

    /**
     * @brief Processes the events received by the game window.
     * This method checks for events such as mouse clicks and keyboard input and updates the game accordingly.
     */
    void processEvents();

    /**
     * @brief Renders the block path on the game screen.
     * This method displays the sequence of blocks that the player needs to remember.
     */
    void renderPath();

    /**
     * @brief Advances to the next level of the game.
     * This method increases the current step index, updates the score, and resets the block sequence rendering.
     */
    void nextLevel();

    /**
     * @brief Renders a specific step of the block sequence on the game screen.
     * This method displays a single block on the game screen, using its position and active block color to render it.
     * @param step The index of the step to render.
     */
    void renderStep(int step);

    /**
     * @brief Creates the blocks for the game.
     * This method generates a four Block objects for the game.
     */
    void createBlocks();

    /**
     * @brief Loads the sound effects for the game.
     * This method reads sound files from disk and stores them in memory.
     */
    void loadSounds();

    /**
     * @brief Plays a sound effect for a specific block.
     * This method plays a sound effect corresponding to the color of the given block when it is active or clicked.
     * @param block The index of the block to play a sound for.
     */
    void playSound(int block);

    /**
     * @brief Adds the next step to the block sequence.
     * This method adds the next step index to the block sequence.
     */
    void addStepPath();

    /**
     * @brief Checks if a given mouse click corresponds to the correct block.
     * This method checks if the mouse click occurred within the bounds of a specific block
     * and if the block has the correct color for the current step.
     * @param mousePosition The position of the mouse click.
     * @return The index of the clicked block.
     */
    int checkClick(sf::Vector2i mousePosition);

    /**
     * @brief Checks whether a correct block was clicked according to step.
     * @param clickedBlock Index of clicked block.
     * @return true or false
     */
    bool isCorrectBlock(int clickedBlock);

    sf::RenderWindow mWindow; // Targeted window for drawing elements
    std::vector<int> mSteps; // Vector that is storing blocks sequence
    std::vector<Block> mBlocks; // Vector that is storing all Block objects
    std::vector<sf::SoundBuffer> mSoundBuffers; // Vector that is storing sound buffers
    std::vector<sf::Sound> mSounds; // Vector that is storing sound samples
};

#endif