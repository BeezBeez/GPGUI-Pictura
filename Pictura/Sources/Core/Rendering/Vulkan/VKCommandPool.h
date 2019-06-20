#pragma once
#include <vulkan/vulkan.h>
#include "Core/Rendering/CommandPool.h"

namespace Pictura::Graphics::Vulkan
{
	class VKRenderer;
	class PICTURA_API VKCommandPool final : public CommandPool
	{
	public:
		VKCommandPool(VKRenderer* renderer);

		~VKCommandPool();

		VkCommandPool* GetVkCmdPool() { return &_commandPool; }

	private:
		VKRenderer* vkr;
		VkCommandPool _commandPool = {};
	};
}
