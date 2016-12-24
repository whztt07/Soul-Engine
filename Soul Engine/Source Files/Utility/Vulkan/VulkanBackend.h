#pragma once

#include "Utility\Includes\GLFWIncludes.h"
#include "VulkanUtility.h"

#include "Utility\Includes\GLMIncludes.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <array>
#include <set>
#include <unordered_map>



VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);

void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);


struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct VulkanVertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(VulkanVertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(VulkanVertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(VulkanVertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(VulkanVertex, texCoord);

		return attributeDescriptions;
	}

	bool operator==(const VulkanVertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}

	friend void swap(VulkanVertex& a, VulkanVertex& b)
	{
		using std::swap; // bring in swap for built-in types

		swap(a.pos, b.pos);
		swap(a.color, b.color);
		swap(a.texCoord, b.texCoord);
	}
};

namespace std {
	template<> struct hash<VulkanVertex> {
		size_t operator()(VulkanVertex const& vertex) const {
			return ((hash<float>()(vertex.pos.x) ^
				hash<float>()(vertex.pos.y) ^
				hash<float>()(vertex.pos.z) ^
				(hash<float>()(vertex.color.x) << 1) ^
				(hash<float>()(vertex.color.y) << 1) ^
				(hash<float>()(vertex.color.z) << 1)) >> 1) ^
				(hash<float>()(vertex.texCoord.x) << 1) ^
				(hash<float>()(vertex.texCoord.y) << 1);
		}
	};
}

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

class VulkanBackend{

public:
	static VulkanBackend& GetInstance()
	{
		static VulkanBackend    instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	VulkanBackend(VulkanBackend const&) = delete;
	void operator=(VulkanBackend const&) = delete;

	void AddWindow(GLFWwindow*, int width, int height);

	static void OnWindowResized(GLFWwindow* window, int width, int height);
	void UpdateVulkanProjection();
	void DrawFrame(GLFWwindow * window, int width, int height);
	void IdleDevice();

private:
	VulkanBackend() {};

	const std::vector<const char*> validationLayers = std::vector<const char*> {
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> deviceExtensions = std::vector<const char*> {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif


	const std::vector<VulkanVertex> vertices = std::vector<VulkanVertex> {
		{ { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ { 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
		{ { -0.5f, 0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
	};

	const std::vector<uint32_t> indices = std::vector<uint32_t> {
		0, 1, 2, 2, 3, 0,
	};

	std::vector<GLFWwindow*> windows;


	VulkanWrapper<VkInstance> instance{ vkDestroyInstance };

	VulkanWrapper<VkDebugReportCallbackEXT> callback{ instance, DestroyDebugReportCallbackEXT };

	VulkanWrapper<VkSurfaceKHR> surface{ instance, vkDestroySurfaceKHR };



	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	VulkanWrapper<VkDevice> device{ vkDestroyDevice };



	VkQueue graphicsQueue;

	VkQueue presentQueue;


	VulkanWrapper<VkSwapchainKHR> swapChain{ device, vkDestroySwapchainKHR };

	std::vector<void*> swapImageData;
	std::vector<VulkanWrapper<VkImage>> swapChainImages;
	std::vector<VkImage> swapChainReal;


	VkFormat swapChainImageFormat;

	VkExtent2D swapChainExtent;

	std::vector<VulkanWrapper<VkImageView>> swapChainImageViews;

	std::vector<VulkanWrapper<VkFramebuffer>> swapChainFramebuffers;

	VulkanWrapper<VkRenderPass> renderPass{ device, vkDestroyRenderPass };

	VulkanWrapper<VkDescriptorSetLayout> descriptorSetLayout{ device, vkDestroyDescriptorSetLayout };

	VulkanWrapper<VkPipelineLayout> pipelineLayout{ device, vkDestroyPipelineLayout };

	VulkanWrapper<VkPipeline> graphicsPipeline{ device, vkDestroyPipeline };



	VulkanWrapper<VkCommandPool> commandPool{ device, vkDestroyCommandPool };



	VulkanWrapper<VkImage> depthImage{ device, vkDestroyImage };

	VulkanWrapper<VkDeviceMemory> depthImageMemory{ device, vkFreeMemory };

	VulkanWrapper<VkImageView> depthImageView{ device, vkDestroyImageView };



	//VulkanWrapper<VkImage> textureImage{ device, vkDestroyImage };

	std::vector<VulkanWrapper<VkDeviceMemory>> textureImageMemory;

	//VulkanWrapper<VkImageView> textureImageView{ device, vkDestroyImageView };

	//VulkanWrapper<VkSampler> textureSampler{ device, vkDestroySampler };


	VulkanWrapper<VkBuffer> vertexBuffer{ device, vkDestroyBuffer };

	VulkanWrapper<VkDeviceMemory> vertexBufferMemory{ device, vkFreeMemory };

	VulkanWrapper<VkBuffer> indexBuffer{ device, vkDestroyBuffer };

	VulkanWrapper<VkDeviceMemory> indexBufferMemory{ device, vkFreeMemory };



	VulkanWrapper<VkBuffer> uniformStagingBuffer{ device, vkDestroyBuffer };

	VulkanWrapper<VkDeviceMemory> uniformStagingBufferMemory{ device, vkFreeMemory };

	VulkanWrapper<VkBuffer> uniformBuffer{ device, vkDestroyBuffer };

	VulkanWrapper<VkDeviceMemory> uniformBufferMemory{ device, vkFreeMemory };



	VulkanWrapper<VkDescriptorPool> descriptorPool{ device, vkDestroyDescriptorPool };

	VkDescriptorSet descriptorSet;



	std::vector<VkCommandBuffer> commandBuffers;



	VulkanWrapper<VkSemaphore> imageAvailableSemaphore{ device, vkDestroySemaphore };

	VulkanWrapper<VkSemaphore> renderFinishedSemaphore{ device, vkDestroySemaphore };


	void InitVulkan(int width, int height);

	void RecreateSwapChain(GLFWwindow * window, int width, int height);

	void CreateInstance();

	void SetupDebugCallback();

	void CreateSurface(GLFWwindow* window);

	void PickVulkanDevice();

	void CreateVulkanLogical();

	void CreateSwapChain(GLFWwindow * window);

	void CreateImageViews(int width, int height);

	void CreateRenderPass();

	void CreateDescriptorSetLayout();

	void CreateGraphicsPipeline();

	void CreateFramebuffers();

	void CreateCommandPool();

	void CreateDepthResources();

	VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat FindDepthFormat();

	bool HasStencilComponent(VkFormat format);

	void CreateTextureImage();

	void CreateTextureImageView();

	void CreateTextureSampler();

	void CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VulkanWrapper<VkImageView>& imageView);

	void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VulkanWrapper<VkImage>& image, VulkanWrapper<VkDeviceMemory>& imageMemory);

	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	void CopyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height);

	void CreateVertexBuffer();

	void CreateIndexBuffer();

	void CreateUniformBuffer();

	void CreateDescriptorPool();

	void CreateDescriptorSet();

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VulkanWrapper<VkBuffer>& buffer, VulkanWrapper<VkDeviceMemory>& bufferMemory);

	VkCommandBuffer beginSingleTimeCommands();

	void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	void CreateCommandBuffers();

	void CreateSemaphores();

	void CreateShaderModule(const std::vector<char>& code, VulkanWrapper<VkShaderModule>& shaderModule);

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow * window);

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

	bool IsDeviceSuitable(VkPhysicalDevice device);

	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	std::vector<const char*> GetRequiredExtensions();
	bool CheckValidationLayerSupport();
	static std::vector<char> ReadFile(const std::string& filename);

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);




};