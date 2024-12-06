#include "AoC.hpp"

#ifdef Day6
static std::ifstream file;

using Position = std::pair<i32, i32>;
using MapRow = std::vector<char>;

enum class Direction
{
    UP = 0,
    DOWN,
    RIGHT,
    LEFT
};

static auto VisitTile(std::vector<MapRow>& map, Position& currentPos, i32& distinct, i32 x, i32 y) -> bool
{
    if (map[y][x] == '.' || map[y][x] == 'X')
    {
        currentPos = { x, y };

        if (map[y][x] == '.')
        {
            map[y][x] = 'X';
            ++distinct;
        }
        return true;
    }
    return false;
}

static auto Part1(std::vector<MapRow> map, Position currentPos) -> i32
{
    i32 distinctPositions = 1;
    Direction direction = Direction::UP;

    bool over = false;
    while (!over)
    {
        auto [currentX, currentY] = currentPos;

        switch (direction)
        {
            case Direction::UP:
                over = currentY - 1 < 0;

                if (!over && !VisitTile(map, currentPos, distinctPositions, currentX, currentY - 1))
                    direction = Direction::RIGHT;
                break;
            case Direction::DOWN:
                over = currentY + 1 >= map.size();

                if (!over && !VisitTile(map, currentPos, distinctPositions, currentX, currentY + 1))
                    direction = Direction::LEFT;
                break;
            case Direction::RIGHT:
                over = currentX + 1 >= map[0].size();

                if (!over && !VisitTile(map, currentPos, distinctPositions, currentX + 1, currentY))
                    direction = Direction::DOWN;
                break;
            case Direction::LEFT:
                over = currentX - 1 < 0;

                if (!over && !VisitTile(map, currentPos, distinctPositions, currentX - 1, currentY))
                    direction = Direction::UP;
                break;
        }
    }

    return distinctPositions;
}

static auto Part2(std::vector<MapRow>& map, Position currentPos) -> i32
{
    Direction direction = Direction::UP;
    Position originalPosition = currentPos;

    i32 totalInfiniteLoops = 0;
    i32 distinctPositions = 0;
    for (i32 i = 0; i < map.size(); ++i)
    {
        for (i32 j = 0; j < map[0].size(); ++j)
        {
            if (map[i][j] == '#')
                continue;

            map[i][j] = '#';
            currentPos = originalPosition;
            direction = Direction::UP;

            i32 count = 0;
            bool over = false;
            while (!over)
            {
                auto [currentX, currentY] = currentPos;

                switch (direction)
                {
                    case Direction::UP:
                        over = currentY - 1 < 0;

                        if (!over && !VisitTile(map, currentPos, distinctPositions, currentX, currentY - 1))
                            direction = Direction::RIGHT;
                        break;
                    case Direction::DOWN:
                        over = currentY + 1 >= map.size();

                        if (!over && !VisitTile(map, currentPos, distinctPositions, currentX, currentY + 1))
                            direction = Direction::LEFT;
                        break;
                    case Direction::RIGHT:
                        over = currentX + 1 >= map[0].size();

                        if (!over && !VisitTile(map, currentPos, distinctPositions, currentX + 1, currentY))
                            direction = Direction::DOWN;
                        break;
                    case Direction::LEFT:
                        over = currentX - 1 < 0;

                        if (!over && !VisitTile(map, currentPos, distinctPositions, currentX - 1, currentY))
                            direction = Direction::UP;
                        break;
                }
                ++count;

                if (count > 10000)
                {
                    ++totalInfiniteLoops;
                    break;
                }
            }
            map[i][j] = '.';
        }
    }

    return totalInfiniteLoops;
}

static auto Part1_2() -> std::pair<i32, i32>
{
    std::vector<MapRow> map;
    Position currentPos;

    std::string line;
    for (i32 row = 0; std::getline(file, line); ++row)
    {
        char tile;
        std::stringstream ss(line);

        MapRow mapRow;
        for (i32 col = 0; ss >> tile; ++col)
        {
            if (tile == '^')
            {
                currentPos = { col, row };
                tile = 'X';
            }
            mapRow.push_back(tile);
        }
        map.push_back(mapRow);
    }

    return { Part1(map, currentPos), Part2(map, currentPos) };
}

auto main() -> i32
{
    std::println("============== Advent of Code - Day 6 ==============");

    Timer timer;
    file.open("input/Day6.txt");
    std::println("Time taken to open file: {}", timer.Elapsed());
    timer.Reset();

    auto [pt1, pt2] = Part1_2();
    std::println("Part 1: {}, Part 2: {}, execution took: {}", pt1, pt2, timer.Elapsed());

    std::println("====================================================");
    return 0;
}
#endif
