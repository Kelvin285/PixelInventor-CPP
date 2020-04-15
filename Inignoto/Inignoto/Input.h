#pragma once
#include "Settings.h"
#include "InputSetting.h"
#include "Camera.h"
class Inignoto;
class Input
{
public:
	static void doInput();
private:
	static void updateCamera();
	static void doGameInput();
};

