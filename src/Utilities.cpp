#include "Utilities.hpp"

auto String::Split(std::string& str, std::string_view delimiter) -> std::vector<std::string>
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);

    return tokens;
}

Timer::Timer()
    : mStartTime{std::chrono::high_resolution_clock::now()}
{

}

auto Timer::Elapsed() -> std::string
{
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - mStartTime).count();

    const auto hours = duration / (1'000ll * 1'000 * 60 * 60);
    duration %= (1'000ll * 1'000 * 60 * 60);
    const auto minutes = duration / (1'000ll * 1'000 * 60);
    duration %= (1'000ll * 1'000 * 60);
    const auto seconds = duration / (1'000ll * 1'000);
    duration %= (1'000ll * 1'000);
    const auto milliseconds = duration / 1'000ll;
    const auto microseconds = duration % 1'000ll;

    std::ostringstream out;
    if (hours > 0)
    {
        out << hours << "h ";
    }
    if (hours > 0 || minutes > 0)
    {
        out << minutes << "m ";
    }
    if (seconds > 0 || minutes > 0)
    {
        out << seconds << "s ";
    }
    if (milliseconds > 0 || seconds > 0)
    {
        out << milliseconds << "ms ";
    }
    if (milliseconds > 0 || microseconds > 0)
    {
        out << microseconds << "us ";
    }
    return out.str();
}

void Timer::Reset()
{
    mStartTime = std::chrono::high_resolution_clock::now();
}