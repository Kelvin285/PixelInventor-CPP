#include "VBO.h"
#include "Inignoto.h"

void VBO::createIndexBuffer() {
	VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
	if (bufferSize == 0) created = false;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
	if (stagingBuffer == 0 || stagingBufferMemory == 0) created = false;

	void* data;
	vkMapMemory(Inignoto::game->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	if (data == nullptr || data == 0) created = false;
	memcpy(data, indices.data(), (size_t)bufferSize);
	if (data != nullptr && data != 0) created = true;
	vkUnmapMemory(Inignoto::game->device, stagingBufferMemory);

	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);
	
	Inignoto::game->copyBuffer(stagingBuffer, indexBuffer, bufferSize);
	if (indexBuffer == 0 || indexBufferMemory == 0) created = false;
	vkDestroyBuffer(Inignoto::game->device, stagingBuffer, nullptr);
	vkFreeMemory(Inignoto::game->device, stagingBufferMemory, nullptr);
}

void VBO::createUniformBuffers() {
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	uniformBuffers.resize(Inignoto::game->swapChainImages.size());
	uniformBuffersMemory.resize(Inignoto::game->swapChainImages.size());
	for (size_t i = 0; i < Inignoto::game->swapChainImages.size(); i++) {
		Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
	}
}

void VBO::render(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int i) {
	if (i >= descriptorSets.size()) return;
	if (!created) return;
	if (!visible) return;
	if (vertices.size() == 0) return;
	VkBuffer vertexBuffers[] = { vertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	

	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

	vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);

	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);

	vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
}

void VBO::updateUniformBuffer(VkExtent2D swapChainExtent, size_t currentImage) {
	if (!created) return;
	if (!visible) return;
	if (vertices.size() == 0) return;
	if (indices.size() == 0) return;
	UniformBufferObject ubo = {};

	//eye position, center position, up axis
	if (orthographic == false) {
		ubo.model = glm::translate(glm::mat4(1.0f), position);
		ubo.model = glm::rotate(ubo.model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		ubo.model = glm::rotate(ubo.model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		ubo.model = glm::rotate(ubo.model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.model = glm::scale(ubo.model, scale * glm::vec3(1, -1, 1));
		ubo.view = glm::lookAt(-Camera::position, -Camera::position + Camera::getForward(), Camera::getUp());
		ubo.proj = glm::perspective(glm::radians(Settings::ACTUAL_FOV), swapChainExtent.width / (float)swapChainExtent.height, Constants::Z_NEAR, Constants::Z_FAR);
	}
	else {
		ubo.model = glm::mat4(1.0f);

		ubo.view = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
		ubo.proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1000.0f);
		ubo.proj[0][0] *= -1; //flips the x-coordinate

	}
	ubo.proj[1][1] *= -1; //flips the y-coordinate so the image is rendered the right way
	void* data;
	vkMapMemory(Inignoto::game->device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vkUnmapMemory(Inignoto::game->device, uniformBuffersMemory[currentImage]);
}

void VBO::createDescriptorSets() {
	std::vector<VkDescriptorSetLayout> layouts(Inignoto::game->swapChainImages.size(), Inignoto::game->descriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = descriptorPool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size());
	allocInfo.pSetLayouts = layouts.data();

	descriptorSets.resize(Inignoto::game->swapChainImages.size());
	if (vkAllocateDescriptorSets(Inignoto::game->device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate descriptor sets!");
	}

	for (size_t i = 0; i < Inignoto::game->swapChainImages.size(); i++) {
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
	poolSize.descriptorCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size());

	std::array<VkDescriptorPoolSize, 2> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size());
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(Inignoto::game->swapChainImages.size());

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(Inignoto::game->swapChainImages.size());

	if (vkCreateDescriptorPool(Inignoto::game->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}

void VBO::createVertexBuffer() {
	bool cancreate = true;
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
	if (sizeof(vertices[0]) * vertices.size() == 0) {
		std::cout << "Cannot create!" << std::endl;
		created = false;
		cancreate = false;
	}
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	if (bufferSize == 0 || stagingBuffer == 0 || stagingBufferMemory == 0) {
		cancreate = false;
	}

	void* data;
	vkMapMemory(Inignoto::game->device, stagingBufferMemory, 0, bufferSize, 0, &data);
	if (data == nullptr || data == 0) cancreate = false;
	memcpy(data, vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(Inignoto::game->device, stagingBufferMemory);
	
	Inignoto::game->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
	if (vertexBuffer == 0 || vertexBufferMemory == 0) cancreate = false;
	Inignoto::game->copyBuffer(stagingBuffer, vertexBuffer, bufferSize);
	if (vertexBuffer != 0) cancreate = true;
	vkDestroyBuffer(Inignoto::game->device, stagingBuffer, nullptr);
	vkFreeMemory(Inignoto::game->device, stagingBufferMemory, nullptr);
	created = cancreate;

	createIndexBuffer();
	createUniformBuffers();
	createDescriptorPool();
	createDescriptorSets();
	for (auto at : vertices) {
		if (glm::isnan(at.color).x || glm::isnan(at.color).y || glm::isnan(at.color).z) {
			std::cout << "NAN COLOR!" << std::endl;
			created = false;
			break;
		}
		if (glm::isnan(at.pos).x || glm::isnan(at.pos).y || glm::isnan(at.pos).z) {
			std::cout << "NAN POS!" << std::endl;
			created = false;
			break;
		}
		if (glm::isnan(at.texCoord).x || glm::isnan(at.texCoord).y) {
			std::cout << "NAN TEXCOORD!" << std::endl;
			created = false;
			break;
		}
	}
}

void VBO::dispose() {
	std::cout << "DISPOSE!" << std::endl;
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