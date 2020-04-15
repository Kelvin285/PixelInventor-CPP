#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "GLFW/glfw3.h"
#include <set>

class InputSetting;
class Settings
{
public:
	static float FOV;
	static float ACTUAL_FOV;
	static float MOUSE_SENSITIVITY;
	static int VIEW_DISTANCE;
	static int VERTICAL_VIEW_DISTANCE;
	static bool HEAD_BOB;
	static bool CASCADED_SHADOWS;
	static bool SHADOWS;
	static bool REFLECTIONS;
	static float EXPOSURE;
	static bool POST_PROCESSING;
	static bool DISTANCE_BLUR;
	static int frameSkip;
	
	static std::unordered_map<std::string, InputSetting> inputs;

	static InputSetting JUMP;
	static InputSetting SNEAK;
	static InputSetting RUN;
	static InputSetting EXIT;
	static InputSetting INVENTORY;
	static InputSetting FORWARD;
	static InputSetting BACKWARD;
	static InputSetting LEFT;
	static InputSetting RIGHT;
	static InputSetting ATTACK;
	static InputSetting USE;

	static std::unordered_map<int, bool> keys;
	static std::unordered_map<int, bool> pressedKey;
	static std::unordered_map<int, bool> buttons;
	static std::unordered_map<int, bool> pressedButton;

	static void loadSettings();
	static void saveSettings();
	static std::string getSaveString(std::string a, int b);
	static std::string getSaveString(std::string a, float b);
	static std::string getSaveString(std::string a, bool b);
	static std::string getSaveString(std::string a, std::string b);

	static bool isKeyDown(int key);
	static bool isKeyJustDown(int key);
	static bool isMouseButtonDown(int button);
	static bool isMouseButtonJustDown(int button);

};

