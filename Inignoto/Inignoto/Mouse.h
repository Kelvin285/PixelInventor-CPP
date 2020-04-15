#pragma once
class Mouse
{
public:
	static float x;
	static float y;
	static bool locked;

	static float lastX;
	static float lastY;

	static void update();
};

