#pragma once
#include <chrono>
#include <iostream>
#include "MathHelper.h"

using namespace std::chrono;
class FPSCounter
{
public:
	static nanoseconds getNanoseconds();
	static long getTime();
	static void start();
	static void updateFPS();
	static void startUpdate();
	static void endUpdate();
	static double getDelta();
	static int getFPS();
private:
	static int fps;
	static long lastFPS;
	static nanoseconds currentTime;
	static nanoseconds lastTime;
	static double delta;
	static long totalGameTime;
	static const long MIN_DELTA;
};

