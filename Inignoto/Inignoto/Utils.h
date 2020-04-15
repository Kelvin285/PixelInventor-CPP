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
};