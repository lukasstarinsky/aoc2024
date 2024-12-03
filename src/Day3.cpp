#include "AoC.hpp"

#ifdef Day3
static std::ifstream file;

static auto Part1_2() -> std::pair<i32, i32>
{
    std::regex pattern(R"(mul\(\d{1,},\d{1,}\)|don't|do)");
    std::string line;
    i32 pt1 = 0, pt2 = 0;
    bool enabled = true;

    while (std::getline(file, line))
    {
        for (std::smatch match; std::regex_search(line, match, pattern); )
        {
            if (match.str() == "don't")
            {
                enabled = false;
            }
            else if (match.str() == "do")
            {
                enabled = true;
            }
            else
            {
                i32 a, b;
                sscanf_s(match.str().c_str(), "mul(%d,%d)", &a, &b);
                pt1 += a * b;
                if (enabled)
                {
                    pt2 += a * b;
                }
            }
            line = match.suffix();
        }
    }

    return { pt1, pt2 };
}

auto main() -> i32
{
    std::println("============== Advent of Code - Day 3 ==============");

    Timer timer;
    file.open("input/Day3.txt");
    std::println("Time taken to open file: {}", timer.Elapsed());
    timer.Reset();

    auto [pt1, pt2] = Part1_2();
    std::println("Part 1: {}, Part 2: {}, execution took: {}", pt1, pt2, timer.Elapsed());

    std::println("====================================================");
    return 0;
}
#endif