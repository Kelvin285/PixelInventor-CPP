#include "InputSetting.h"
#include "Settings.h"

InputSetting::InputSetting(int id, bool mouse, std::string name) {
	this->id = id;
	this->mouse = mouse;
	this->name = name;
}

void InputSetting::set(int id, bool mouse) {
	this->id = id;
	this->mouse = mouse;
}

bool InputSetting::isPressed() {
	if (mouse) return Settings::isMouseButtonDown(id);
	return Settings::isKeyDown(id);
}

bool InputSetting::isJustPressed() {
	if (mouse) return Settings::isMouseButtonJustDown(id);
	return Settings::isKeyJustDown(id);
}

std::string InputSetting::getName() {
	return name;
}

std::string InputSetting::getTranslatedName() {
	return Translation::translateText(this->name);
}

void InputSetting::read(std::string b) {
	std::vector<std::string> data = Utils::split(b, ',');
	
	if (data.size() == 2) {
		std::istringstream iss(data[0]);
		int number;
		iss >> number;
		set(number, data[1] == "true" ? true : false);
	}
}

std::string InputSetting::write() {
	std::ostringstream ss;
	ss << id;
	std::string s(ss.str());

	std::ostringstream ss2;
	ss2 << mouse;
	std::string s2(ss2.str());
	return s + "," + s2;
}