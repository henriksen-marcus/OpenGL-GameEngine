#include <chrono>
#include <string>

class Timer {
public:
    Timer() {
        mIsRunning = false;
        mElapsedTime = std::chrono::duration<double>::zero();
    }

    void Start() {
        if (!mIsRunning) {
            mIsRunning = true;
            mStartTime = std::chrono::steady_clock::now();
        }
    }

    void Pause() {
        if (mIsRunning) {
            mIsRunning = false;
            mElapsedTime += std::chrono::steady_clock::now() - mStartTime;
        }
    }

    void Stop() {
        if (mIsRunning) {
            mIsRunning = false;
            mElapsedTime += std::chrono::steady_clock::now() - mStartTime;
        }
    }

    void Reset() {
        mStartTime = std::chrono::steady_clock::now();
        mElapsedTime = std::chrono::duration<double>::zero();
        mIsRunning = true;
    }

    std::string GetDurationAsString() {
        auto durationInMs = std::chrono::duration_cast<std::chrono::milliseconds>(mElapsedTime).count();
        return std::to_string(durationInMs) + "ms";
    }

    long long GetDuration() {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(mElapsedTime + (mIsRunning ? std::chrono::steady_clock::now() - mStartTime : std::chrono::steady_clock::duration{ 0 }));
        mElapsedTime = std::chrono::duration<double>::zero();
        return duration.count();
    }

private:
    bool mIsRunning;
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    std::chrono::duration<double> mElapsedTime;
};
