#include "SnakeGame.h"


int main(void)
{
    constexpr int WIDTH = 120;
    constexpr int HEIGHT = 30;
    const std::wstring gameTitle = L"Snake Game";
    SnakeGame snakeGame(gameTitle, WIDTH, HEIGHT);

    if (!snakeGame.initializeConsole())
    {
        return EXIT_FAILURE;
    }

    return snakeGame.gameLoop();
}