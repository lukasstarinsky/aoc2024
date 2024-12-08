#pragma once

#include <vector>
#include <string>
#include <chrono>

namespace String
{
    auto Split(std::string& str, std::string_view delimiter) -> std::vector<std::string>;
}

template<typename T>
T ConcatenateIntegers(T a, T b)
{
    T bDigits = (b == 0) ? 1 : static_cast<T>(std::log10(b)) + 1;
    return a * static_cast<T>(std::pow(10, bDigits)) + b;
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