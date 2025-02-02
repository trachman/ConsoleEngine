#include "Block.hpp"


Block::Block(const int row, const int col, const WORD attr)
: m_attr(attr),
  m_row(row),
  m_col(col)
{
    // Nothing else to do
}


Block::operator CHAR_INFO(void) const
{
    CHAR_INFO charInfo;
    charInfo.Attributes = m_attr;
    charInfo.Char.UnicodeChar = m_rep;
    return charInfo;
}


bool Block::operator==(const Block& RHS) const
{
    return m_row == RHS.m_row && m_col == RHS.m_col;
}


void Block::move(const ConsoleEngine::Input direction)
{
    switch (direction)
    {
        case ConsoleEngine::Input::LEFT:  this->moveLeft(); break;
        case ConsoleEngine::Input::RIGHT: this->moveRight(); break;
        case ConsoleEngine::Input::UP:    this->moveUp(); break;
        case ConsoleEngine::Input::DOWN:  this->moveDown(); break;
        default: break;
    }
}


void Block::drawToOutputBuffer(std::vector<CHAR_INFO>& outputBuffer, const int width) const
{
    const int maxOffset = static_cast<int>(outputBuffer.size());

    int offset = this->offset(width);

    if (offset < 0 || offset >= maxOffset)
    {
        offset = 0;
    }

    outputBuffer.at(offset) = *this;
}


bool Block::isOutsideExtents(const int width, const int height) const
{
    return m_row < 0 || m_col < 0 || m_row >= height || m_col >= width;
}


std::pair<int, int> Block::location(void) const
{
    return { m_row, m_col };
}


void Block::moveDown(void)
{
    m_row += 1;
}


void Block::moveRight(void)
{
    m_col += 1;
}


void Block::moveUp(void)
{
    m_row -= 1;
}


void Block::moveLeft(void)
{
    m_col -= 1;
}


int Block::offset(const int width) const
{
    return Utilities::computeTheOffset(m_row, m_col, width);
}
