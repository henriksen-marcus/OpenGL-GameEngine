#pragma once
#include <string>

class RenderWindow;

class DebugLogger
{
public:
	static DebugLogger& GetInstance()
	{
		static DebugLogger instance;
		return instance;
	}

	void Print(std::string message);

	void SetRenderWindow(RenderWindow* rw);

private:
	DebugLogger(){}
	~DebugLogger(){}

	DebugLogger(const DebugLogger&) = delete;
	DebugLogger& operator = (const DebugLogger&) = delete;

	RenderWindow* mRenderWindow;
};

