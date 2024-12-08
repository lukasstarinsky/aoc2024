#include "AoC.hpp"

#ifdef Day7
static std::ifstream file;

enum class Operator
{
    ADD = 0,
    MULTIPLY,
    CONCAT,
};

static void IncrementOperatorSet(std::vector<i8>& operatorSet, i32 limit = 2)
{
    for (i8& i: operatorSet)
    {
        ++i;

        if (i < limit)
            return;
        else
            i = 0;
    }
}

static auto SolveEquationPt1(const std::vector<i64>& nums, i64 targetResult) -> i64
{
    std::vector<i8> operatorSet;
    operatorSet.resize(nums.size() - 1, 0);

    while (true)
    {
        i64 result = nums[0];
        for (i32 i = 1; i < nums.size(); ++i)
        {
            switch (static_cast<Operator>(operatorSet[i - 1]))
            {
                case Operator::ADD:
                    result += nums[i];
                    break;
                case Operator::MULTIPLY:
                    result *= nums[i];
                    break;
                case Operator::CONCAT:
                    break;
            }
        }
        if (result == targetResult)
            return true;

        if (!std::any_of(operatorSet.begin(), operatorSet.end(), [](i8 num) { return num == 0; }))
            break;

        IncrementOperatorSet(operatorSet);
    }

    return false;
}

static auto SolveEquationPt2(const std::vector<i64>& nums, i64 targetResult) -> i64
{
    std::vector<i8> operatorSet;
    operatorSet.resize(nums.size() - 1, 0);

    while (true)
    {
        i64 result = nums[0];
        for (i32 i = 1; i < nums.size(); ++i)
        {
            switch (static_cast<Operator>(operatorSet[i - 1]))
            {
                case Operator::ADD:
                    result += nums[i];
                    break;
                case Operator::MULTIPLY:
                    result *= nums[i];
                    break;
                case Operator::CONCAT:
                    result = ConcatenateIntegers(result, nums[i]);
                    break;
            }
        }
        if (result == targetResult)
            return true;

        if (!std::any_of(operatorSet.begin(), operatorSet.end(), [](i8 num) { return num == 0 || num == 1; }))
            break;

        IncrementOperatorSet(operatorSet, 3);
    }

    return false;
}

static auto Part1_2() -> std::pair<i64, i64>
{
    std::string line;
    std::unordered_map<i64, std::vector<i64>> equations;

    while (std::getline(file, line))
    {
        auto parts = String::Split(line, ": ");
        assert(parts.size() == 2);
        i64 index = std::stoll(parts[0]);

        std::stringstream ss(parts[1]);
        equations[index] = { std::istream_iterator<i32>(ss), {} };
    }

    i64 pt1 = 0, pt2 = 0;
    for (const auto& [testValue, nums]: equations)
    {
        if (SolveEquationPt1(nums, testValue))
            pt1 += testValue;
        if (SolveEquationPt2(nums, testValue))
            pt2 += testValue;
    }

    return { pt1, pt2 };
}

auto main() -> i32
{
    std::println("============== Advent of Code - Day 7 ==============");

    Timer timer;
    file.open("input/Day7.txt");
    std::println("Time taken to open file: {}", timer.Elapsed());
    timer.Reset();

    auto [pt1, pt2] = Part1_2();
    std::println("Part 1: {}, Part 2: {}, execution took: {}", pt1, pt2, timer.Elapsed());

    std::println("====================================================");
    return 0;
}
#endif