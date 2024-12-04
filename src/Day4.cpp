#include "AoC.hpp"

#ifdef Day4
static std::ifstream file;

static auto Part1_2() -> std::pair<i32, i32>
{
    i32 pt1 = 0, pt2 = 0;
    std::vector<std::string> input(std::istream_iterator<std::string>(file), {});

    for (i32 i = 0; i < input.size(); ++i)
    {
        for (i32 j = 0; j < input[i].size(); ++j)
        {
            // Search horizontal
            if (j + 3 < input[i].size() && input[i][j] == 'X' && input[i][j + 1] == 'M' && input[i][j + 2] == 'A' && input[i][j + 3] == 'S')
                ++pt1;

            if (j > 2 && input[i][j] == 'X' && input[i][j - 1] == 'M' && input[i][j - 2] == 'A' && input[i][j - 3] == 'S')
                ++pt1;

            // Search down
            if (i + 3 < input.size())
            {
                if (input[i][j] == 'X' && input[i + 1][j] == 'M' && input[i + 2][j] == 'A' && input[i + 3][j] == 'S')
                    ++pt1;

                // Search down left
                if (j > 2 && input[i][j] == 'X' && input[i + 1][j - 1] == 'M' && input[i + 2][j - 2] == 'A' && input[i + 3][j - 3] == 'S')
                    ++pt1;

                // Search down right
                if (j + 3 < input[i].size() && input[i][j] == 'X' && input[i + 1][j + 1] == 'M' && input[i + 2][j + 2] == 'A' && input[i + 3][j + 3] == 'S')
                    ++pt1;
            }

            // Search up
            if (i > 2)
            {
                if (input[i][j] == 'X' && input[i - 1][j] == 'M' && input[i - 2][j] == 'A' && input[i - 3][j] == 'S')
                    ++pt1;

                // Search up left
                if (j > 2 && input[i][j] == 'X' && input[i - 1][j - 1] == 'M' && input[i - 2][j - 2] == 'A' && input[i - 3][j - 3] == 'S')
                    ++pt1;

                // Search up right
                if (j + 3 < input[i].size() && input[i][j] == 'X' && input[i - 1][j + 1] == 'M' && input[i - 2][j + 2] == 'A' && input[i - 3][j + 3] == 'S')
                    ++pt1;
            }

            // Search X, part 2
            if (j + 2 < input[i].size() && i + 2 < input.size() && input[i + 1][j + 1] == 'A')
            {
                if ((input[i][j] == 'M' && input[i + 2][j + 2] == 'S' ||
                    input[i][j] == 'S' && input[i + 2][j + 2] == 'M') &&
                    (input[i + 2][j] == 'M' && input[i][j + 2] == 'S' ||
                    input[i + 2][j] == 'S' && input[i][j + 2] == 'M'))
                    ++pt2;
            }
        }
    }

    return { pt1, pt2 };
}

auto main() -> i32
{
    std::println("============== Advent of Code - Day 4 ==============");

    Timer timer;
    file.open("input/Day4.txt");
    std::println("Time taken to open file: {}", timer.Elapsed());
    timer.Reset();

    auto [pt1, pt2] = Part1_2();
    std::println("Part 1: {}, Part 2: {}, execution took: {}", pt1, pt2, timer.Elapsed());

    std::println("====================================================");
    return 0;
}
#endif