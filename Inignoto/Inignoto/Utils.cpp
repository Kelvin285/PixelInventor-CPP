#include "Utils.h"

GLFWwindow* Utils::window;
unsigned int Utils::FRAME_WIDTH = 1920 / 2;
unsigned int Utils::FRAME_HEIGHT = 1080 / 2;
bool Utils::WINDOW_FOCUSED = false;
bool Utils::framebufferResized = false;


std::vector<char> Utils::readFile(const std::string modID, const std::string& filename) {
	std::ifstream file("assets/"+modID+"/"+filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return buffer;
}

std::vector<std::string> Utils::split(std::string in, const char split) {
	std::vector<std::string> data;
	std::string str = "";
	for (size_t i = 0; i < in.length(); i++) {
		if (in[i] == split || i == in.length() - 1) {
			data.push_back(std::string(str));
			str = "";
		}
		else {
			str += in[i];
		}
	}
	return data;
}

void Utils::replace(std::string* a, std::string b, std::string c)
{
	size_t i = a->find(b);
	size_t len = b.length();

	a->replace(i, i + len, c);
}
