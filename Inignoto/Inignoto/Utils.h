#pragma once
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <array>
#include <optional>
#include <set>
#include <sstream>
#include <unordered_map>

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};
class Utils
{
public:
	
	

	static GLFWwindow* window;
	static unsigned int FRAME_WIDTH;
	static unsigned int FRAME_HEIGHT;
	static bool WINDOW_FOCUSED;
	static bool framebufferResized;

	static std::vector<char> readFile(const std::string modID, const std::string& filename);

	static std::vector<std::string> split(std::string str, const char split);
	static void replace(std::string* a, std::string b, std::string c);

	static int getInt(std::string line) {
		std::istringstream iss(line);
		int number;
		iss >> number;
		return number;
	}
	static float getFloat(std::string line) {
		std::istringstream iss(line);
		float number;
		iss >> number;
		return number;
	}
	static bool getBool(std::string line) {
		std::istringstream iss(line);
		int number;
		iss >> number;
		return number;
	}
	static double getDouble(std::string line) {
		std::istringstream iss(line);
		double number;
		iss >> number;
		return number;
	}

	static std::unordered_map<std::string, std::string> getData(std::string str) {
		std::unordered_map<std::string, std::string> mapdata;
		std::string s = "";
		for (size_t i = 0; i < str.length(); i++) {
			if (str[i] == '\n' || i == str.length() - 1) {
				if (i == str.length() - 1) {
					s += str[i];
				}
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

					for (size_t j = 0; j < data[0].length(); j++) {
						char c = data[0][j];
						if (start && c == '"') break;
						if (start) b += c;
						if (c == '"') start = true;
					}

					if (!a.empty() && !b.empty()) {
						mapdata.insert({ a, b });
					}
				}

				s = "";
			}
			else {
				s += str[i];
			}
		}
		return mapdata;
	}
};