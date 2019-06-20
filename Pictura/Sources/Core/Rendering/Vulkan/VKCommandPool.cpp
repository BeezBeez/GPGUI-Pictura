#include "PicturaPCH.h"
#include "VKCommandPool.h"
#include "VKRenderer.h"

namespace Pictura::Graphics::Vulkan
{
	VKCommandPool::VKCommandPool(VKRenderer* renderer)
	{
		vkr = renderer;
		VkCommandPoolCreateInfo poolCreateInfo{};
		poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolCreateInfo.queueFamilyIndex = vkr->GetGraphicsFamilyIndex();
		poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		vkr->CheckErrors(vkCreateCommandPool(*vkr->GetDevice(), &poolCreateInfo, nullptr, &_commandPool));

		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Info("Vulkan command pool created!","VULKAN");
		}
	}

	VKCommandPool::~VKCommandPool()
	{
		vkDestroyCommandPool(*vkr->GetDevice(), _commandPool, nullptr);
	}
}
