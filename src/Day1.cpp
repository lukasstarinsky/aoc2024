#include "AoC.hpp"

static std::vector<int> leftVals, rightVals;

static void LoadData()
{
    std::ifstream file("input/Day1.txt");
    i32 left, right;

    while (file >> left >> right)
    {
        leftVals.push_back(left);
        rightVals.push_back(right);
    }
    assert(leftVals.size() == rightVals.size() && "Vectors are not the same size.");
}

static auto Part1() -> i32
{
    auto leftCopy = leftVals;
    auto rightCopy = rightVals;

    std::sort(leftCopy.begin(), leftCopy.end());
    std::sort(rightCopy.begin(), rightCopy.end());

    i32 sum = 0;
    for (i32 i = 0; i < leftCopy.size(); ++i)
    {
        sum += std::abs(leftCopy[i] - rightCopy[i]);
    }

    return sum;
}

static auto Part2() -> i64
{
    i64 similarityScore = 0;

    for (i32 leftVal: leftVals)
    {
        i64 rightCount = std::count_if(rightVals.begin(), rightVals.end(), [&](i32 val) { return leftVal == val; });
        similarityScore += leftVal * rightCount;
    }

    return similarityScore;
}

#ifdef Day1
auto main() -> i32
{
    std::println("Day 1");

    Timer timer;
    LoadData();
    std::println("Time taken to load file: {}", timer.Elapsed());
    timer.Reset();

    auto p1 = Part1();
    std::println("Part 1: {}, execution took: {}", p1, timer.Elapsed());
    timer.Reset();

    auto p2 = Part2();
    std::println("Part 2: {}, execution took: {}", p2, timer.Elapsed());

    return 0;
}
#endif