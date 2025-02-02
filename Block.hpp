#pragma once

#include "ConsoleEngine.hpp"
#include <utility>


class Block
{
public:
    Block(void) = delete;
    Block(const int row, const int col, const WORD attr = 7);
    ~Block(void) = default;

    operator CHAR_INFO(void) const;
    bool operator==(const Block& RHS) const;

    void move(const ConsoleEngine::Input direction);
    void drawToOutputBuffer(std::vector<CHAR_INFO>& outputBuffer, const int width) const;
    [[nodiscard]] bool isOutsideExtents(const int width, const int height) const;
    [[nodiscard]] std::pair<int, int> location(void) const;

private:
    [[nodiscard]] int offset(const int width) const;

    void moveDown(void);
    void moveRight(void);
    void moveUp(void);
    void moveLeft(void);

    static constexpr wchar_t m_rep = 0x2588; // White Vertical Rectangle
    WORD m_attr;
    int m_row;
    int m_col;
};
