#include "Snake.hpp"

#include <random>
#include <set>
#include <utility>


static std::random_device g_dev;
static std::mt19937 g_rng(g_dev());
static std::uniform_int_distribution<std::mt19937::result_type> g_distCol(1,119);
static std::uniform_int_distribution<std::mt19937::result_type> g_distRow(1,29);


Snake::Snake(const int row, const int col)
: m_currentTime(0.0),
  m_body({})
{
    constexpr size_t reserveSize = 500;
    m_body.clear();
    m_body.reserve(reserveSize);
    m_body.emplace_back(row, col);
}


void Snake::move(
    const ConsoleEngine::Input direction,
    const double deltaTime,
    Block& candy,
    size_t& score)
{
    if (this->isNoOpCommand(direction) || this->checkDeltaTime(deltaTime))
    {
        return; // Do nothing
    }

    m_currentTime = 0.0;

    Block copyOfLastBlock = m_body.back();

    for (size_t i = m_body.size() - 1; i > 0; --i)
    {
        m_body.at(i) = m_body.at(i - 1);
    }

    m_body.front().move(direction);

    if (this->headIsEqualTo(candy))
    {
        ++score;
        this->grow(copyOfLastBlock);
        this->makeNewCandy(candy);
    }
}


void Snake::drawToOutputBuffer(std::vector<CHAR_INFO>& outputBuffer, const int width) const
{
    for (const Block& block : m_body)
    {
        block.drawToOutputBuffer(outputBuffer, width);
    }
}


bool Snake::hasSelfIntersection(void) const
{
    std::set<std::pair<int, int>> locations;

    for (const Block& block : m_body)
    {
        const std::pair<int, int> location = block.location();

        if (!locations.contains(location))
        {
            locations.insert(location);
        }
        else
        {
            return true;
        }
    }

    return false;
}


bool Snake::isOutsideExtents(const int width, const int height) const
{
    return m_body.front().isOutsideExtents(width, height);
}


void Snake::grow(Block& newBlock)
{
    m_body.emplace_back(std::move(newBlock));
}


void Snake::makeNewCandy(Block& candy)
{
    const int newRow = g_distRow(g_rng);
    const int newCol = g_distCol(g_rng);
    candy = Block(newRow, newCol, FOREGROUND_GREEN);
}


bool Snake::headIsEqualTo(const Block& candy) const
{
    const Block& head = m_body.front();

    return head == candy;
}


bool Snake::isNoOpCommand(const ConsoleEngine::Input command) const
{
    return command == ConsoleEngine::Input::NONE
        || command == ConsoleEngine::Input::UNDEFINED
        || command == ConsoleEngine::Input::QUIT;
}


bool Snake::checkDeltaTime(const double deltaTime)
{
    m_currentTime += deltaTime;

    return m_currentTime < m_vel;
}
