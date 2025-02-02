#pragma once

#include "Snake.hpp"
#include "ConsoleEngine.hpp"
#include <string>


class SnakeGame : public ConsoleEngine
{
public:
    SnakeGame(const std::wstring& title, const int width, const int height);
    virtual ~SnakeGame(void) = default;

    SnakeGame(void) = delete;
    SnakeGame(const SnakeGame& RHS) = delete;
    SnakeGame(SnakeGame&& RHS) = delete;
    SnakeGame& operator=(const SnakeGame& RHS) = delete;
    SnakeGame& operator=(SnakeGame&& RHS) = delete;

    [[nodiscard]] bool update(const double deltaTime) override;
    [[nodiscard]] bool render(void) override;

private:
    void resetGameState(void) override;
    void onGameBegin(void) override;
    PlayAgain onGameEnd(void) const override;
    void handleInputEvents(void);
    void drawFPSToOutputBuffer(void);
    void drawScoreToOutputBuffer(void);

    size_t m_score;
    Input m_currentDirection;
    Snake m_snake;
    Block m_candy;
};
