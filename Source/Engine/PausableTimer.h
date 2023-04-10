#pragma once

#include <QElapsedTimer>

/* Class that extends QElapsedTimer to support pausing. */
class PauseableTimer : public QElapsedTimer
{
public:
    PauseableTimer() : QElapsedTimer(), mPaused(false), mPauseDuration(0) {}

    void start()
    {
        QElapsedTimer::start();
        mPaused = false;
        mPauseDuration = 0;
    }

    void pause()
    {
        if (!mPaused) {
            mPaused = true;
            mPauseStart = QElapsedTimer::elapsed();
        }
    }

    void resume()
    {
        if (mPaused) {
            mPaused = false;
            mPauseDuration += QElapsedTimer::elapsed() - mPauseStart;
        }
    }

    qint64 elapsed() const
    {
        if (mPaused) return mPauseDuration;
        else return QElapsedTimer::elapsed() - mPauseDuration;
    }

private:
    bool mPaused;
    qint64 mPauseStart;
    qint64 mPauseDuration;
};

