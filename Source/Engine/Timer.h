#pragma once

#include <chrono>
#include <string>

class Timer {
public:
    Timer() {
        mIsRunning = false;
        mElapsedTime = std::chrono::duration<double>::zero();
    }

    void Start() {
        mIsRunning = true;
        mStartTime = std::chrono::high_resolution_clock::now();
    }

    void Pause() {
        mElapsedTime += std::chrono::high_resolution_clock::now() - mStartTime;
        mIsRunning = false;
    }

    void Stop() {
        if (mIsRunning) {
            mElapsedTime += std::chrono::high_resolution_clock::now() - mStartTime;
            mIsRunning = false;
        }
    }

    void Reset() {
        mElapsedTime = std::chrono::duration<double>::zero();
        mIsRunning = false;
    }

    std::string GetDurationAsString() {
        auto durationInMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mStartTime).count();
        return std::to_string(durationInMs) + "ms";
    }

    long long GetDuration() {
        mElapsedTime += std::chrono::high_resolution_clock::now() - mStartTime;
        auto durationInMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mStartTime).count();
        return durationInMs;
    }

private:
    bool mIsRunning;
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
    std::chrono::duration<double> mElapsedTime;
};
