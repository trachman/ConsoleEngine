#include "SnakeGame.h"

#include <cmath>


SnakeGame::SnakeGame(const std::wstring& title, const int width, const int height)
: m_score(0),
  m_currentDirection(Input::NONE),
  m_snake(0,0),
  m_candy(0,0),
  ConsoleEngine(title, width, height)
{
    this->resetGameState();
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


void SnakeGame::resetGameState(void)
{
    m_score = 0,
    m_snake = Snake(this->height() / 2, this->width() / 2);
    m_currentDirection = Input::NONE;
    m_candy = Block(20, 20, FOREGROUND_GREEN);
    m_running = true;
}


void SnakeGame::onGameBegin(void)
{
    // Landing page.
    const std::wstring welcomeMessage = L"Welcome to Snake!";
    const std::wstring instructions = L"Use your Arrow Keys or W, A, S, D to move.";
    const std::wstring quitInstructions = L"Press 'q' or 'ESC' to quit.";
    const std::wstring playInstructions = L"Press any of the above keys to play.";
    this->drawStringToBuffer(welcomeMessage, 11, 40);
    this->drawStringToBuffer(instructions, 12, 40);
    this->drawStringToBuffer(quitInstructions, 13, 40);
    this->drawStringToBuffer(playInstructions, 14, 40);

    while (true)
    {
        if (!this->input())
        {
            break;
        }

        if (!this->ConsoleEngine::render())
        {
            break;
        }

        if (!m_inputCommands.empty())
        {
            break;
        }
    }
}


ConsoleEngine::PlayAgain SnakeGame::onGameEnd(void) const
{
    std::wstring scoreString = L"Your score was: " + std::to_wstring(m_score) + L"\nYou wanna play again?";

    constexpr int YES_INT = 6;
    const int response = MessageBox(
        nullptr,
        scoreString.data(),
        TEXT("Uh oh!"),
        MB_YESNO);

    return response == YES_INT ? PlayAgain::YES : PlayAgain::NO;
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
