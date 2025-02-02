#include "SnakeGame.h"

#include <cmath>


SnakeGame::SnakeGame(const std::wstring& title, const int width, const int height)
: m_score(0),
  m_snake(height / 2, width / 2),
  m_currentDirection(Input::UP),
  m_candy(20, 20, FOREGROUND_GREEN),
  ConsoleEngine(title, width, height)
{
    // Nothing else to do
}


SnakeGame::~SnakeGame(void)
{
    // Nothing else to do
}


bool SnakeGame::update(const double deltaTime)
{
    // Handle input events
    this->handleInputEvents();

    // Move the snake
    m_snake.move(m_currentDirection, deltaTime, m_candy, m_score);

    // Check for self intersections and out of bounds
    m_running = m_running && !m_snake.hasSelfIntersection();
    m_running = m_running && !m_snake.isOutsideExtents(this->width(), this->height());

    return true;
}


bool SnakeGame::render(void)
{
    // Update the output buffer with our new game state
    this->drawFPSToOutputBuffer();
    this->drawScoreToOutputBuffer();
    m_snake.drawToOutputBuffer(m_outputBuffer, m_width);
    m_candy.drawToOutputBuffer(m_outputBuffer, m_width);

    return this->ConsoleEngine::render();
}


void SnakeGame::handleInputEvents(void)
{
    for (const Input input : m_inputCommands)
    {
        if (input == Input::QUIT || input == Input::UNDEFINED)
        {
            // Break out of the game loop
            m_running = false;
            break;
        }

        // Update the latest direction
        m_currentDirection = input;
    }
}


void SnakeGame::drawFPSToOutputBuffer(void)
{
    const int fpsInt = static_cast<int>(std::ceil(m_fps));
    const std::wstring fpsStr = L"FPS: " + std::to_wstring(fpsInt);

    this->drawStringToBuffer(fpsStr, 0, 0);
}


void SnakeGame::drawScoreToOutputBuffer(void)
{
    const std::wstring scoreStr = L"Score: " + std::to_wstring(m_score);

    this->drawStringToBuffer(scoreStr, 1, 0);
}
