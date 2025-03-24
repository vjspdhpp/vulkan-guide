// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.
//> intro
#pragma once

#include <vk_types.h>
#include <vk_descriptors.h>

struct DeletionQueue {
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	};

	void flush() {
		for (auto it = deletors.begin(); it != deletors.end(); it++) {
			(*it)();
		}
		deletors.clear();
	}
};

struct FrameData {
	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;
	VkSemaphore _swapchainSemaphore, _renderSemaphore;
	VkFence _renderFence;//Fence(栅栏) 用于CPU和GPU之间的同步
	DeletionQueue _deletionQueue;
};

constexpr unsigned int FRAME_OVERLAP = 2;


class VulkanEngine {
public:

	bool _isInitialized{ false };
	int _frameNumber {0};
	bool stop_rendering{ false };
	VkExtent2D _windowExtent{ 1700 , 900 };
	FrameData _frames[FRAME_OVERLAP];
	struct SDL_Window* _window{ nullptr };

	VkQueue _graphicsQueue;
	uint32_t _graphicsQueueFamily;

	VkInstance _instance;
	VkDebugUtilsMessengerEXT  _debug_messenger;
	VkPhysicalDevice _chosenGPU;
	VkDevice _device;
	VkSurfaceKHR  _surface;

	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat;

	std::vector<VkImage> _swapchainImages;
	std::vector<VkImageView> _swapchainImageViews;
	VkExtent2D _swapchainExtent;
	DeletionQueue _mainDeletionQueue;
	VmaAllocator _allocator;

	// draw resources
	AllocatedImage _drawImage;
	VkExtent2D _drawExtent;

	DescriptorAllocator globalDescriptorAllocator;
	VkDescriptorSet _drawImageDescriptors;
	VkDescriptorSetLayout _drawImageDescriptorLayout;

	VkPipeline _gradientPipeline;
	VkPipelineLayout _gradientPipelineLayout;


	static VulkanEngine& Get();

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();

	void init_vulkan();

	void init_swapchain();

	void init_commands();

	void init_sync_structures();

	FrameData& get_current_frame(){return _frames[_frameNumber % FRAME_OVERLAP];}

private:
	void create_swapchain(uint32_t width, uint32_t height);
	void destroy_swapchain();

	void draw_background(VkCommandBuffer cmd);

	void init_descriptors();

	void init_pipelines();

	void init_background_pipelines();
};
//< intro