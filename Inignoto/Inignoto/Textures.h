#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <streambuf>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <array>
#include <iostream>
#include "growl/packer.hpp"


class Inignoto;
struct Texture {
	int width, height;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;
};

struct TextureSpace {
	std::string name;
	int X;
	int Y;
	int W;
	int H;

public :
	std::array<glm::vec2, 4> getTextureCoords(int IMAGE_WIDTH, int IMAGE_HEIGHT, float u, float v, float w, float h) {
		float u1 = ((float)X + u * (float)W) / (float)IMAGE_WIDTH;
		float v1 = ((float)Y + v * (float)H) / (float)IMAGE_HEIGHT;
		float u2 = ((float)X + w * (float)W) / (float)IMAGE_WIDTH;
		float v2 = ((float)Y + h * (float)H) / (float)IMAGE_HEIGHT;
		std::array<glm::vec2, 4> texCoords = {
		glm::vec2(u1, v1),
		glm::vec2(u1, v2),
		glm::vec2(u2, v2),
		glm::vec2(u2, v1)
		};
		return texCoords;
	}
};

struct PackedTexture {
	unsigned char* imageData;
	int x_off, y_off;
	int width, height;
	const char* name;
	const char* filepath;
};

class Textures
{

public:


	static void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	static Texture TEXTURE_ATLAS;

	static std::vector<Texture> textures;
	static std::vector<TextureSpace> textureSpaces;

	static int IMAGE_WIDTH;
	static int IMAGE_HEIGHT;

	static unsigned int num_textures;

	static TextureSpace* getSpaceFor(std::string texture);

	static Texture createTextureImage(std::string modID, std::string path);

	static void init();

	static void dispose();


};

