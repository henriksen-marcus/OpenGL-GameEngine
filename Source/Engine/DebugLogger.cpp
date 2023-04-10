#include "DebugLogger.h"

#include "logger.h"
#include "renderwindow.h"

void DebugLogger::Print(std::string message)
{
	if (mRenderWindow)
		mRenderWindow->mLogger->logText(message, LogType::WARNING);
}

void DebugLogger::SetRenderWindow(RenderWindow* rw)
{
	mRenderWindow = rw;
}
