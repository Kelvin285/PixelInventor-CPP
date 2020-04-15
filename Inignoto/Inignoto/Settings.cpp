#include "Settings.h"
#include "InputSetting.h"


namespace fs = std::filesystem;

float Settings::FOV = 60.0f;
float Settings::ACTUAL_FOV = 60.0f;
float Settings::MOUSE_SENSITIVITY = 0.1f;

int Settings::VIEW_DISTANCE = 8;
int Settings::VERTICAL_VIEW_DISTANCE = 2;

bool Settings::HEAD_BOB = true;

bool Settings::CASCADED_SHADOWS = true;
bool Settings::SHADOWS = true;
bool Settings::REFLECTIONS = true;

float Settings::EXPOSURE = 1.5f;

bool Settings::POST_PROCESSING = true;

bool Settings::DISTANCE_BLUR = false;

int Settings::frameSkip = 0;

std::unordered_map<std::string, InputSetting> Settings::inputs;

InputSetting Settings::JUMP(GLFW_KEY_SPACE, false, "Inignoto:input.jump");
InputSetting Settings::SNEAK(GLFW_KEY_LEFT_SHIFT, false, "Inignoto:input.sneak");
InputSetting Settings::RUN(GLFW_KEY_LEFT_CONTROL, false, "Inignoto:input.run");
InputSetting Settings::EXIT(GLFW_KEY_ESCAPE, false, "Inignoto:input.exit");
InputSetting Settings::INVENTORY(GLFW_KEY_E, false, "Inignoto:input.inventory");
InputSetting Settings::FORWARD(GLFW_KEY_W, false, "Inignoto:input.forward");
InputSetting Settings::BACKWARD(GLFW_KEY_S, false, "Inignoto:input.backward");
InputSetting Settings::LEFT(GLFW_KEY_A, false, "Inignoto:input.left");
InputSetting Settings::RIGHT(GLFW_KEY_D, false, "Inignoto:input.right");
InputSetting Settings::ATTACK(0, true, "Inignoto:input.attack");
InputSetting Settings::USE(1, true, "Inignoto:input.use");

std::unordered_map<int, bool> Settings::keys;
std::unordered_map<int, bool> Settings::pressedKey;
std::unordered_map<int, bool> Settings::buttons;
std::unordered_map<int, bool> Settings::pressedButton;

void Settings::loadSettings() {
	std::string path("Inignoto/settings.txt");
	if (!fs::exists(path)) {
		return;
	}
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	

	std::string s = "";

	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == '\n' || i == str.length() - 1) {
			std::vector<std::string> data = Utils::split(s, '=');
			
			if (data.size() == 2) {
				bool start = false;
				std::string a = "";
				std::string b = "";

				for (size_t j = 0; j < data[0].length(); j++) {
					char c = data[0][j];
					if (start && c == '"') break;
					if (start) a += c;
					if (c == '"') start = true;
				}

				start = false;
				for (size_t j = 0; j < data[1].length(); j++) {
					char c = data[1][j];
					if (start && c == '"') break;
					if (start) b += c;
					if (c == '"') start = true;
				}
				std::cout << a << ", " << b << std::endl;
				if (!a.empty() && !b.empty()) {
					if (a == "FOV") FOV = Utils::getFloat(b);
					if (a == "MOUSE_SENSITIVITY") MOUSE_SENSITIVITY = Utils::getFloat(b);
					if (a == "VIEW_DISTANCE") VIEW_DISTANCE = Utils::getInt(b);
					if (a == "VERTICAL_VIEW_DISTANCE") VERTICAL_VIEW_DISTANCE = Utils::getInt(b);
					if (a == "HEAD_BOB") HEAD_BOB = Utils::getBool(b);
					if (a == "SHADOWS") SHADOWS = Utils::getBool(b);
					if (a == "DISTANCE_BLUR") DISTANCE_BLUR = Utils::getBool(b);
					if (a == "REFLECTIONS") REFLECTIONS = Utils::getBool(b);
					if (a == "EXPOSURE") EXPOSURE = Utils::getFloat(b);
					if (a == "POST_PROCESSING") POST_PROCESSING = Utils::getBool(b);
					if (a == "FRAME_SKIP") frameSkip = Utils::getInt(b);
					if (a == "JUMP") JUMP.read(b);
					if (a == "SNEAK") SNEAK.read(b);
					if (a == "RUN") RUN.read(b);
					if (a == "EXIT") EXIT.read(b);
					if (a == "INVENTORY") INVENTORY.read(b);
					if (a == "BACKWARD") BACKWARD.read(b);
					if (a == "LEFT") LEFT.read(b);
					if (a == "RIGHT") RIGHT.read(b);
					if (a == "ATTACK") ATTACK.read(b);
					if (a == "USE") USE.read(b);
				}
			}
			s = std::string("");
		}
		else {
			s += str[i];
		}
		
	}
}

void Settings::saveSettings() {
	std::string str;
	str += getSaveString("FOV", FOV);
	str += getSaveString("MOUSE_SENSITIVITY", MOUSE_SENSITIVITY);
	str += getSaveString("VIEW_DISTANCE", VIEW_DISTANCE);
	str += getSaveString("VERTICAL_VIEW_DISTANCE", VERTICAL_VIEW_DISTANCE);
	str += getSaveString("HEAD_BOB", HEAD_BOB);
	str += getSaveString("SHADOWS", SHADOWS);
	str += getSaveString("DISTANCE_BLUR", DISTANCE_BLUR);
	str += getSaveString("REFLECTIONS", REFLECTIONS);
	str += getSaveString("EXPOSURE", EXPOSURE);
	str += getSaveString("POST_PROCESSING", POST_PROCESSING);
	str += getSaveString("FRAME_SKIP", frameSkip);
	str += getSaveString("JUMP", JUMP.write());
	str += getSaveString("SNEAK", SNEAK.write());
	str += getSaveString("RUN", RUN.write());
	str += getSaveString("EXIT", EXIT.write());
	str += getSaveString("INVENTORY", INVENTORY.write());
	str += getSaveString("FORWARD", FORWARD.write());
	str += getSaveString("BACKWARD", BACKWARD.write());
	str += getSaveString("LEFT", LEFT.write());
	str += getSaveString("RIGHT", RIGHT.write());
	str += getSaveString("ATTACK", ATTACK.write());
	str += getSaveString("USE", USE.write());
	std::ofstream out;
	if (!fs::is_directory("Inignoto/")) {
		fs::create_directory("Inignoto/");
	}
	out.open("Inignoto/settings.txt");
	out << str;
	out.close();
}

std::string Settings::getSaveString(std::string a, int b) {
	std::ostringstream ss;
	ss << b;
	std::string s(ss.str());
	return std::string("\"" + a + "\"=\"" + s + "\"\n");
}

std::string Settings::getSaveString(std::string a, float b) {
	std::ostringstream ss;
	ss << b;
	std::string s(ss.str());
	return std::string("\"" + a + "\"=\"" + s + "\"\n");
}

std::string Settings::getSaveString(std::string a, bool b) {
	std::ostringstream ss;
	ss << b;
	std::string s(ss.str());
	return std::string("\"" + a + "\"=\"" + s + "\"\n");
}

std::string Settings::getSaveString(std::string a, std::string b) {
	return std::string("\"" + a + "\"=\"" + b + "\"\n");
}

bool Settings::isKeyDown(int key) {
	if (keys.count(key) != 0) {
		return keys[key];
	}
	std::pair<int, bool> pair(key, false);
	keys.insert(pair);
	return false;
}

bool Settings::isKeyJustDown(int key) {
	if (pressedKey.count(key) != 0) {
		if (pressedKey[key]) {
			pressedKey[key] = false;
			return true;
		}
	}
	std::pair<int, bool> pair(key, false);
	pressedKey.insert(pair);
	return false;
}

bool Settings::isMouseButtonDown(int key) {
	if (buttons.count(key) != 0) {
		return buttons[key];
	}
	std::pair<int, bool> pair(key, false);
	buttons.insert(pair);
	return false;
}

bool Settings::isMouseButtonJustDown(int key) {
	if (pressedButton.count(key) != 0) {
		if (pressedButton[key]) {
			pressedButton[key] = false;
			return true;
		}
	}
	std::pair<int, bool> pair(key, false);
	pressedButton.insert(pair);
	return false;
}