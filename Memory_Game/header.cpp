#include "header.hpp"

// This is the implementation of the Block class that is used in the MemoryGameProject.

Block::Block(sf::Vector2f size, sf::Color color, float thickness, sf::Vector2f position) :
color(color),
block_shape(size),
active_color(alterColor(color, COLOR_CHANGE_FACTOR))
{
    // Initialize the properties of the block shape
    block_shape.setFillColor(color);
    block_shape.setOutlineColor(sf::Color::Black);
    block_shape.setOutlineThickness(thickness);
    block_shape.setPosition(position);
}

void Block::render(sf::RenderWindow &window) const {
    window.draw(block_shape);
}

void Block::toggleBlockColor() {
    // Check if the current color is the normal color
    if (block_shape.getFillColor() == color)
        block_shape.setFillColor(active_color);
    else
        block_shape.setFillColor(color);
}

sf::Color Block::alterColor(sf::Color color, float factor) const {
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

// This is the implementation of the Score class that is used in the MemoryGameProject.

Score::Score(float radius, float thickness, sf::Vector2f position) :
current_level(1),
color(sf::Color::Cyan),
render_path_color(sf::Color::Magenta),
scoreFont(),
score_shape(radius),
scoreText()
{
    // Initialize the properties of the score shape
    score_shape.setFillColor(color);
    score_shape.setOutlineColor(sf::Color::Black);
    score_shape.setOutlineThickness(thickness);
    score_shape.setPosition(position);

    // Create a font and edit score text
    if (!scoreFont.loadFromFile(FONT_PATH)) {
        std::cout << "ERROR FONT FILE" << std::endl;
        exit(1);
    }

    // Initialize the properties of the score text
    scoreText.setFont(scoreFont);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setStyle(sf::Text::Bold);
    centerScore();
}

void Score::render(sf::RenderWindow &window) const {
    window.draw(score_shape);
    window.draw(scoreText);
}

void Score::toggleScoreColor(bool render_path_state) {
    score_shape.setFillColor(render_path_state ? render_path_color : color);
}

void Score::updateScore() {
    current_level++;
    scoreText.setString(std::to_string(current_level));

    // Check for milestone levels and center text in case of getting a new digit
    const std::vector<int> milestoneLevels = {10, 100, 1000};
    if (std::find(milestoneLevels.begin(), milestoneLevels.end(), current_level) != milestoneLevels.end())
        centerScore();
}

void Score::setText(const std::string text, unsigned int font_size) {
    scoreText.setString(text);
    scoreText.setCharacterSize(font_size);
    centerScore();
}

sf::Vector2f Score::getPosition() const {
    return score_shape.getPosition();
}

void Score::centerScore() {
    // Set the origin of the text to its center
    sf::FloatRect textRect = scoreText.getLocalBounds();
    scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    scoreText.setPosition(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
}

// This is the implementation of the MemoryGameProject class

MemoryGameProject::MemoryGameProject() :
    // Initialize window with specified width, height, and title
    mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "MEMORY GAME", sf::Style::Titlebar | sf::Style::Close),
    step_idx(0),
    display_path(true),
    score(SCORE_RADIUS, OUTLINE_THICKNESS, sf::Vector2f(BLOCK_WIDTH-SCORE_RADIUS, BLOCK_HEIGHT-SCORE_RADIUS))
{
    mWindow.setFramerateLimit(FPS_LIMIT);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // calculate the center position of the screen
    int centerX = (desktop.width - mWindow.getSize().x) / 2;
    int centerY = (desktop.height - mWindow.getSize().y) / 2;

    mWindow.setPosition(sf::Vector2i(centerX, centerY));

    // Seed the random number generator with the current time
    srand(time(nullptr));

    createBlocks();
    addStepPath();
    loadSounds();
}

void MemoryGameProject::awaitStart() {
    // Render initial block and wait for user to start
    for (Block& b : mBlocks)
        b.render(mWindow);

    // Set informational text
    score.setText("PRESS SPACE", FONT_SIZE/3.5f);
    score.render(mWindow);
    mWindow.display();

    // Await for start input
    while (mWindow.isOpen()) {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mWindow.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                mWindow.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                score.setText(std::to_string(score.current_level), FONT_SIZE);
                return;
            }
        }
    }
}

void MemoryGameProject::run() {
    awaitStart();
    while (mWindow.isOpen()) {
        renderPath();
    }
}

void MemoryGameProject::processEvents() {
    sf::Event event;

    // Process events in the event queue
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mWindow.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            mWindow.close();
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !display_path) { // If user clicks the left button on mouse and currently game awaits for user to click
            sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow); // Get mouse position relative to the window
            int clickedBlock = checkClick(mousePosition);
            playSound(clickedBlock);
            if (isCorrectBlock(clickedBlock))
                step_idx++;
            else {
                std::cout << "Incorrect!" << std::endl;
                mWindow.close();
            }
        }
    }
}

void MemoryGameProject::renderPath() {
    if (display_path) {
        // Display current block sequence
        score.toggleScoreColor(true);
        for (int i=0; i<score.current_level; i++)
            renderStep(i);
        display_path = !display_path;

    } else {
        // Await for correct user inputs
        if (step_idx >= score.current_level) {
            nextLevel();
        } else
            processEvents();
    }
}

void MemoryGameProject::nextLevel() {
    display_path = !display_path;
    step_idx = 0;
    score.updateScore();
    addStepPath();
    sf::sleep(sf::seconds(2.0));
}

void MemoryGameProject::renderStep(int step) {
    // Render block colors with one currently active step
    mWindow.clear();
    mBlocks[mSteps[step]].toggleBlockColor();
    for (Block& b : mBlocks)
        b.render(mWindow);
    score.render(mWindow);
    mWindow.display();
    playSound(mSteps[step]);

    // Pause for given time before rendering the next frame during path display
    sf::sleep(sf::seconds(PAUSE_TIME));

    // Render all normal block colors and sleep for a brief amount of time to make clearer pauses
    mWindow.clear();
    mBlocks[mSteps[step]].toggleBlockColor();
    for (Block& b : mBlocks)
        b.render(mWindow);
    if (step+1 == score.current_level)
        score.toggleScoreColor(false);
    score.render(mWindow);
    mWindow.display();

    sf::sleep(sf::seconds(0.2f));
}

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

void MemoryGameProject::loadSounds() {
    // Load all sounds for each block
    for (int i=0; i < mBlocks.size(); i++) {
        std::string filename = "Sounds/simonSound" + std::to_string(i) + ".wav";
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filename)) {
            std::cout << "ERROR SOUND FILE" << std::endl;
            exit(1);
        }

        // Create and store new sound buffer and sound in a corresponding vectors
        mSoundBuffers.push_back(buffer);
        mSounds.push_back(sf::Sound());
    }
}

void MemoryGameProject::playSound(int block) {
    mSounds[block].setBuffer(mSoundBuffers[block]);
    mSounds[block].play();
}

void MemoryGameProject::addStepPath() {
    mSteps.push_back(rand() % mBlocks.size());
}

int MemoryGameProject::checkClick(sf::Vector2i mousePosition) {
    bool isLeft = mousePosition.x < BLOCK_WIDTH;
    bool isTop = mousePosition.y < BLOCK_HEIGHT;

    if (isLeft && isTop)
        return 0;
    else if (!isLeft && isTop)
        return 1;
    else if (isLeft && !isTop)
        return 2;
    else
        return 3;
}

bool MemoryGameProject::isCorrectBlock(int clickedBlock) {
    return clickedBlock == mSteps[step_idx];
}
