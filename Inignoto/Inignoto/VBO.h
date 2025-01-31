#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <string>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include <minmax.h>
#include <math.h>
#include "MathHelper.h"
#include <time.h>

class VBO {
public:

	VBO() = default;

	bool orthographic = false;
	bool created = false;
	bool visible = true;
	float loadValue = 0;
	glm::vec3 position = glm::vec3(0.0);
	glm::vec3 rotation = glm::vec3(0.0);
	glm::vec3 scale = glm::vec3(1.0);

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<VkDescriptorSet> uniformBuffers;
	std::vector<VkDescriptorSet> uniformBuffersMemory;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	bool disposed;

	void createIndexBuffer();

	void createVertexBuffer();

	void dispose();

	void render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int i);
	void updateUniformBuffer(VkExtent2D swapChainExtent, size_t currentImage);
private:
	void createUniformBuffers();

	void createDescriptorPool();

	void createDescriptorSets();
	
};

