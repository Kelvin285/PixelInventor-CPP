#include "VBO.h"
#include "Inignoto.h"

void VBO::createIndexBuffer() {
	VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(Inignoto::game->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices.data(), (size_t)bufferSize);
	vkUnmapMemory(Inignoto::game->device, stagingBufferMemory);

	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	Inignoto::game->copyBuffer(stagingBuffer, indexBuffer, bufferSize);

	vkDestroyBuffer(Inignoto::game->device, stagingBuffer, nullptr);
	vkFreeMemory(Inignoto::game->device, stagingBufferMemory, nullptr);
}

void VBO::createUniformBuffers() {
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	uniformBuffers.resize(Inignoto::game->swapChainImages.size() + 5);
	uniformBuffersMemory.resize(Inignoto::game->swapChainImages.size() + 5);
	for (size_t i = 0; i < Inignoto::game->swapChainImages.size() + 5; i++) {
		Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
	}
}

void VBO::createDescriptorSets() {
	std::vector<VkDescriptorSetLayout> layouts(Inignoto::game->swapChainImages.size() + 5, Inignoto::game->descriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size() + 5);
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(Inignoto::game->swapChainImages.size() + 5);
	if (vkAllocateDescriptorSets(Inignoto::game->device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < Inignoto::game->swapChainImages.size() + 5; i++) {
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkDescriptorImageInfo imageInfo = {};
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;


		std::vector<VkDescriptorImageInfo> information;
		information.resize(Textures::textures.size());
		for (size_t j = 0; j < information.size(); j++) {
			VkDescriptorImageInfo imageInfo = {};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = Textures::textures[j].textureImageView;
			imageInfo.sampler = Textures::textures[j].textureSampler;
			information[j] = imageInfo;
		}
		std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

		descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[0].dstSet = descriptorSets[i];
		descriptorWrites[0].dstBinding = 0;
		descriptorWrites[0].dstArrayElement = 0;
		descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrites[0].descriptorCount = 1;
		descriptorWrites[0].pBufferInfo = &bufferInfo;

		descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrites[1].dstSet = descriptorSets[i];
		descriptorWrites[1].dstBinding = 1;
		descriptorWrites[1].dstArrayElement = 0;
		descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		descriptorWrites[1].descriptorCount = static_cast<uint32_t>(information.size());
		descriptorWrites[1].pImageInfo = information.data();

		vkUpdateDescriptorSets(Inignoto::game->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
	}
}

void VBO::createDescriptorPool() {
	VkDescriptorPoolSize poolSize = {};
	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize.descriptorCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size() + 5);

	std::array<VkDescriptorPoolSize, 2> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size() + 5);
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size() + 5);

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(Inignoto::game->swapChainImages.size() + 5);

	if (vkCreateDescriptorPool(Inignoto::game->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void VBO::createVertexBuffer() {
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(Inignoto::game->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(Inignoto::game->device, stagingBufferMemory);

	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	Inignoto::game->copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

	vkDestroyBuffer(Inignoto::game->device, stagingBuffer, nullptr);
	vkFreeMemory(Inignoto::game->device, stagingBufferMemory, nullptr);
	createIndexBuffer();
	createUniformBuffers();
	createDescriptorPool();
	createDescriptorSets();
}

void VBO::dispose() {
	if (disposed) return;
	for (size_t i = 0; i < uniformBuffers.size(); i++) {
		vkDestroyBuffer(Inignoto::game->device, uniformBuffers[i], nullptr);
		vkFreeMemory(Inignoto::game->device, uniformBuffersMemory[i], nullptr);
	}
	
	vkDestroyDescriptorPool(Inignoto::game->device, descriptorPool, nullptr);

	vkDestroyBuffer(Inignoto::game->device, vertexBuffer, nullptr);
	vkFreeMemory(Inignoto::game->device, vertexBufferMemory, nullptr);
	vkDestroyBuffer(Inignoto::game->device, indexBuffer, nullptr);
	vkFreeMemory(Inignoto::game->device, indexBufferMemory, nullptr);
	disposed = true;
}