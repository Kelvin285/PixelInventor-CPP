#pragma once
#include <string>
#include <vector>
#include "Utils.h"
#include <sstream>
#include "Translation.h"

class InputSetting
{
public:
	InputSetting(int id, bool mouse, std::string name);
	void set(int id, bool mouse);
	bool isPressed();
	bool isJustPressed();
	std::string getName();
	std::string getTranslatedName();
	void read(std::string b);
	std::string write();
private:
	int id;
	bool mouse;
	std::string name;
};

