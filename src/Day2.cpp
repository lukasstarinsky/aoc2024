#include "AoC.hpp"

#ifdef Day2
static std::ifstream file;

static auto IsUnsafe(const std::vector<i32>& levels) -> bool
{
    bool increasing = levels[1] > levels[0];
    return std::adjacent_find(levels.begin(), levels.end(), [increasing](i32 a, i32 b) {
        auto diff = a - b;
        return diff == 0 || (increasing && diff > 0) || (!increasing && diff < 0) || std::abs(diff) > 3;
    }) != levels.end();
}

static auto Part1_2() -> std::pair<i32, i32>
{
    std::string reportLine;

    i32 safeCountPt1 = 0;
    i32 safeCountPt2 = 0;
    while (std::getline(file, reportLine))
    {
        std::stringstream report(reportLine);
        std::vector<i32> levels((std::istream_iterator<i32>(report)), {});

        if (IsUnsafe(levels))
        {
            for (i32 i = 0; i < levels.size(); ++i)
            {
                auto levelsCopy = levels;
                levelsCopy.erase(levelsCopy.begin() + i);
                if (!IsUnsafe(levelsCopy))
                {
                    ++safeCountPt2;
                    break;
                }
            }
        }
        else
        {
            ++safeCountPt1;
            ++safeCountPt2;
        }
    }

    return { safeCountPt1, safeCountPt2 };
}

auto main() -> i32
{
    std::println("============== Advent of Code - Day 2 ==============");

    Timer timer;
    file.open("input/Day2.txt");
    std::println("Time taken to open file: {}", timer.Elapsed());
    timer.Reset();

    auto [pt1, pt2] = Part1_2();
    std::println("Part 1: {}, Part 2: {}, execution took: {}", pt1, pt2, timer.Elapsed());

    std::println("====================================================");
    return 0;
}
#endif