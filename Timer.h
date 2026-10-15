#pragma once
#include <chrono>

// Stopwatch (same style as the Chrono-class example).
class Timer {
    using hrClock = std::chrono::high_resolution_clock;
    using durationDouble = std::chrono::duration<double>;

    std::chrono::time_point<hrClock> start;

public:
    Timer() : start{hrClock::now()} {}
    void reset() { start = hrClock::now(); }
    double elapsed() const {                      // seconds
        return durationDouble(hrClock::now() - start).count();
    }
};
