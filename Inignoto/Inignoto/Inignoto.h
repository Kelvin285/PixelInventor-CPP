#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Translation.h"
#include "Settings.h"
#include "Camera.h"
#include "Input.h"
#include "FPSCounter.h"

#include <chrono>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include "Utils.h"
#include "Constants.h"
#include "Events.h"
#include <string>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include <minmax.h>
#include <math.h>
#include "MathHelper.h"
#include "Textures.h"
#include "VBO.h"
#include <set>
#include "GuiRenderer.h"
#include <thread>
#include "World.h"
#include <mutex>

struct ModifyVBO {
	VBO* vbo;
	int TTL = 20;
};

class Inignoto
{
public:
	static Inignoto* game;
	VkDevice device;
	std::vector<VkImage> swapChainImages;
	VkDescriptorSetLayout descriptorSetLayout;

	void run();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	void addVBO(VBO* vbo, bool now = false);
	void removeVBO(VBO* vbo, bool now = false);

	VBO testVBO;
	VBO testVBO2;

	GuiRenderer guiRenderer;

	World world;

	std::mutex mutex;

	bool needsToRender;
private:
	bool checkingVBOS;
	bool finished;
	bool refreshView;
	bool addedVBO;
	bool removedVBO;

	const int MAX_FRAMES_IN_FLIGHT = 2;

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	VkInstance vk_instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkQueue graphicsQueue;
	VkSurfaceKHR surface;
	VkQueue presentQueue;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkSwapchainKHR swapChain;
	VkRenderPass renderPass;

	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	VkCommandPool commandPool;
	
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	std::vector<VBO*> vbos;
	std::vector<ModifyVBO> removeVbos;
	std::vector<ModifyVBO> addVbos;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;

	size_t currentFrame = 0;

	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<VkCommandBuffer> commandBuffers;
	

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
	
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
	#endif

	void worldUpdateThread();
	void worldSaveThread();

	void threadedRender();

	void updateWorld();

	void createInstance();

	void initWindow();

	void initVulkan();

	void createDepthResources();

	bool hasStencilComponent(VkFormat format);
	
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

	VkFormat findDepthFormat();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	void createVertexBuffer();

	void cleanupSwapChain();

	void createSyncObjects();

	void createCommandBuffers();

	void modifyCommandBuffers(size_t i);

	void createCommandPool();

	void createFramebuffers();

	void createRenderPass();

	void createGraphicsPipeline();

	void createDescriptorSetLayout();

	void recreateSwapChain();

	void createShader(std::string modid, std::string vertex, std::string fragment);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	void createSwapChain();

	void createImageViews();

	void createSurface();

	void pickAndCreatePhysicalDevice();

	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormat);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	
	bool checkValidationLayerSupport();

	void setupDebugMessenger();

	std::vector<const char*> getRequiredExtensions();

	VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	void loop();

	void render();

	void drawFrame();

	void tick();

	void updateUniformBuffer(uint32_t imageIndex);

	void dispose();

	void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

};


//I'm watching you