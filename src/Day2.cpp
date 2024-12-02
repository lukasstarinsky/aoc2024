#include "AoC.hpp"

#ifdef Day2
static std::ifstream file;

auto Part1_2() -> std::pair<i32, i32>
{
    std::string reportLine;

    i32 safeCountPt1 = 0;
    i32 safeCountPt2 = 0;
    while (std::getline(file, reportLine))
    {
        std::stringstream report(reportLine);
        std::vector<i32> levels((std::istream_iterator<i32>(report)), std::istream_iterator<i32>());

        bool unsafe = false;
        bool increasing = levels[1] > levels[0];

        for (i32 i = 0; i < levels.size() - 1; ++i)
        {
            auto diff = levels[i] - levels[i + 1];

            if (diff == 0 || (increasing && diff > 0) || (!increasing && diff < 0) || std::abs(diff) > 3)
            {
                unsafe = true;
                break;
            }
        }

        // If unsafe, brute force erasing each element for part 2
        if (unsafe)
        {
            for (i32 i = 0; i < levels.size(); ++i)
            {
                auto levelsCopy = levels;
                levelsCopy.erase(levelsCopy.begin() + i);

                unsafe = false;
                increasing = levelsCopy[1] > levelsCopy[0];

                for (i32 j = 0; j < levelsCopy.size() - 1; ++j)
                {
                    auto diff = levelsCopy[j] - levelsCopy[j + 1];

                    if (diff == 0 || (increasing && diff > 0) || (!increasing && diff < 0) || std::abs(diff) > 3)
                    {
                        unsafe = true;
                        break;
                    }
                }

                if (!unsafe)
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
    std::println("Day 2");

    Timer timer;
    file.open("input/Day2.txt");
    std::println("Time taken to open file: {}", timer.Elapsed());
    timer.Reset();

    auto [pt1, pt2] = Part1_2();
    std::println("Part 1: {}, Part 2: {}, execution took: {}", pt1, pt2, timer.Elapsed());

    return 0;
}
#endif