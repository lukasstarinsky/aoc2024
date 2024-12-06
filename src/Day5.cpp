#include "AoC.hpp"

#ifdef Day5
static std::ifstream file;

auto Part1_2() -> std::pair<i32, i32>
{
    std::vector<std::vector<i32>> pageUpdates;
    std::vector<std::pair<i32, i32>> pageRules;

    i32 pt1 = 0, pt2 = 0;
    std::string line;
    bool secondSection = false;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        if (line.empty())
        {
            secondSection = true;
            continue;
        }

        if (!secondSection)
        {
            char _;
            i32 x, y;
            ss >> x >> _ >> y;
            pageRules.emplace_back(x, y);
        }
        else
        {
            i32 x;
            std::vector<i32> pageNumbers;
            while (ss >> x)
            {
                char _;
                pageNumbers.push_back(x);
                ss >> _;
            }
            pageUpdates.push_back(pageNumbers);
        }
    }

    for (auto& pageUpdate : pageUpdates)
    {
        std::unordered_map<i32, i32> indexMap;
        for (i32 i = 0; i < pageUpdate.size(); ++i)
        {
            indexMap[pageUpdate[i]] = i;
        }

        std::vector<std::pair<i32, i32>> pageRuleset;
        for (const auto [ruleX, ruleY]: pageRules)
        {
            if (indexMap.contains(ruleX) && indexMap.contains(ruleY))
            {
                pageRuleset.emplace_back(ruleX, ruleY);
            }
        }

        // Part 1
        bool correct = true;
        for (const auto [ruleX, ruleY]: pageRuleset)
        {
            if (indexMap[ruleX] > indexMap[ruleY])
            {
                correct = false;
                break;
            }
        }
        if (correct)
        {
            pt1 += pageUpdate[pageUpdate.size() / 2];
        }

        // Part 2
        std::vector<i32> sorted = pageUpdate;
        std::sort(sorted.begin(), sorted.end(), [&](i32 a, i32 b)
        {
            for (const auto& [ruleX, ruleY] : pageRuleset)
            {
                if (a == ruleX && b == ruleY)
                    return true;
                if (a == ruleY && b == ruleX)
                    return false;
            }
            return false;
        });

        if (pageUpdate != sorted)
        {
            pt2 += sorted[sorted.size() / 2];
        }
    }

    return { pt1, pt2 };
}

auto main() -> i32
{
    std::println("============== Advent of Code - Day 5 ==============");

    Timer timer;
    file.open("input/Day5.txt");
    std::println("Time taken to open file: {}", timer.Elapsed());
    timer.Reset();

    auto [pt1, pt2] = Part1_2();
    std::println("Part 1: {}, Part 2: {}, execution took: {}", pt1, pt2, timer.Elapsed());

    std::println("====================================================");
    return 0;
}
#endif
