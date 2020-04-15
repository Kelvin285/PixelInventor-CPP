#pragma once 
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Textures.h"
#include "Inignoto.h"

std::vector<Texture> Textures::textures;
unsigned int Textures::num_textures;

std::vector<TextureSpace> Textures::textureSpaces;

Texture Textures::TEXTURE_ATLAS;
int Textures::IMAGE_WIDTH;
int Textures::IMAGE_HEIGHT;

void Textures::createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory)
{
	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = usage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateImage(Inignoto::game->device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image!");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(Inignoto::game->device, image, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = Inignoto::game->findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(Inignoto::game->device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate image memory!");
	}

	vkBindImageMemory(Inignoto::game->device, image, imageMemory, 0);
}

Texture Textures::createTextureImage(std::string modID, std::string path) {
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	std::string dir = "assets/" + modID + "/textures/" + path;
	const char* str = dir.c_str();
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(str, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	VkDeviceSize imageSize = texWidth * texHeight * 4;

	Textures::IMAGE_WIDTH = texWidth;
	Textures::IMAGE_HEIGHT = texHeight;

	if (!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}

	Texture texture = {};
	texture.width = texWidth;
	texture.height = texHeight;

	Inignoto::game->createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(Inignoto::game->device, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(Inignoto::game->device, stagingBufferMemory);
	stbi_image_free(pixels);

	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = static_cast<uint32_t>(texWidth);
	imageInfo.extent.height = static_cast<uint32_t>(texHeight);
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.flags = 0;
	if (vkCreateImage(Inignoto::game->device, &imageInfo, nullptr, &texture.textureImage) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(Inignoto::game->device, texture.textureImage, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = Inignoto::game->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	if (vkAllocateMemory(Inignoto::game->device, &allocInfo, nullptr, &texture.textureImageMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate image memory!");
	}

	vkBindImageMemory(Inignoto::game->device, texture.textureImage, texture.textureImageMemory, 0);

	Inignoto::game->transitionImageLayout(texture.textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	Inignoto::game->copyBufferToImage(stagingBuffer, texture.textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));

	Inignoto::game->transitionImageLayout(texture.textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkDestroyBuffer(Inignoto::game->device, stagingBuffer, nullptr);
	vkFreeMemory(Inignoto::game->device, stagingBufferMemory, nullptr);

	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = texture.textureImage;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	if (vkCreateImageView(Inignoto::game->device, &viewInfo, nullptr, &texture.textureImageView) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture image view!");
	}

	//create texture sampler
	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_NEAREST;
	samplerInfo.minFilter = VK_FILTER_NEAREST;
	
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

	samplerInfo.anisotropyEnable = VK_TRUE; // anisotropic filtering.  Disable if performance is a concern
	samplerInfo.maxAnisotropy = 16; // difference is negilable beyond 16

	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;

	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;

	if (vkCreateSampler(Inignoto::game->device, &samplerInfo, nullptr, &texture.textureSampler) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}

	textures.push_back(texture);
	num_textures++;

}

bool compare(std::string A, std::string B) {
	return A == B;
}

TextureSpace* Textures::getSpaceFor(std::string texture) {
	for (size_t i = 0; i < textureSpaces.size(); i++) {
		//std::cout << textureSpaces[i].name << ", " << texture << std::endl;
		if (compare(textureSpaces[i].name, texture)) {
			return &textureSpaces[i];
		}
	}
	return nullptr;
}

void Textures::init()
{
	std::ifstream t("assets/Inignoto/textures/textures.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	std::vector<std::string> data;
	std::string line = "";
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == '\n') {
			data.push_back(std::string(line));
			line = "";
			continue;
		}
		line += str[i];
	}

	for (size_t i = 0; i < data.size(); i++) {
		std::string A = "";
		std::string B = "";
		bool inQuotes = false;
		bool hasEqual = false;
		for (size_t j = 0; j < data[i].length(); j++) {
			if (inQuotes) {
				if (data[i][j] == '"') {
					inQuotes = false;
					continue;
				}
				if (hasEqual == false) {
					A += data[i][j];
				}
				else {
					B += data[i][j];
				}
			}
			else {
				if (data[i][j] == '"') {
					inQuotes = true;
					continue;
				}
				if (data[i][j] == '=') {
					hasEqual = true;
				}
			}
		}
		//A = name
		std::string num = "";

		int X = -1;
		int Y = -1;
		int W = -1;
		int H = -1;

		for (size_t j = 0; j < B.length(); j++) {
			if (B[j] == ',' || j == B.length() - 1) {
				std::istringstream iss(num);
				int number;
				iss >> number;
				
				if (X == -1) X = number;
				else if (Y == -1) Y = number;
				else if (W == -1) W = number;
				else if (H == -1) H = number;

				num = "";
			}
			else {
				if (B[j] == '0' || B[j] == '1' || B[j] == '2' || B[j] == '3' || B[j] == '4' || B[j] == '5' || B[j] == '6' || B[j] == '7' ||
					B[j] == '8' || B[j] == '9')
				num += B[j];
			}
		}
		TextureSpace space = {};
		space.name = A;
		space.X = X;
		space.Y = Y;
		space.W = W;
		space.H = H;
		textureSpaces.push_back(space);
	}
	
	Textures::TEXTURE_ATLAS = createTextureImage("Inignoto", "texture_atlas.png");
}

void Textures::dispose() {
	for (unsigned int i = 0; i < num_textures; i++) {
		Inignoto::game->transitionImageLayout(textures[i].textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

		
		vkDestroySampler(Inignoto::game->device, textures[i].textureSampler, nullptr);

		vkDestroyImageView(Inignoto::game->device, textures[i].textureImageView, nullptr);

		vkDestroyImage(Inignoto::game->device, textures[i].textureImage, nullptr);
		vkFreeMemory(Inignoto::game->device, textures[i].textureImageMemory, nullptr);

	}
}