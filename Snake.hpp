#pragma once

#include "Block.hpp"

#include <vector>


class Snake
{
public:
    Snake(void) = delete;
    Snake(const int row, const int col);
    ~Snake(void) = default;

    void move(
        const ConsoleEngine::Input direction,
        const double deltaTime,
        Block& candy,
        size_t& score);
    void drawToOutputBuffer(std::vector<CHAR_INFO>& outputBuffer, const int width) const;
    [[nodiscard]] bool hasSelfIntersection(void) const;
    [[nodiscard]] bool isOutsideExtents(const int width, const int height) const;

private:
    void grow(Block& newBlock);
    void makeNewCandy(Block& candy);
    [[nodiscard]] bool headIsEqualTo(const Block& candy) const;
    [[nodiscard]] bool isNoOpCommand(const ConsoleEngine::Input command) const;
    [[nodiscard]] bool checkDeltaTime(const double deltaTime);

    static constexpr double m_vel = 0.05; // 1 unit per 0.05 seconds
    double m_currentTime;
    std::vector<Block> m_body;
};
