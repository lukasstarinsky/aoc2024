#pragma once

#include <vector>
#include <string>
#include <chrono>

namespace String
{
    auto Split(std::string& str, std::string_view delimiter) -> std::vector<std::string>;
}

class Timer
{
public:
    Timer();

    auto Elapsed() -> std::string;
    void Reset();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
};