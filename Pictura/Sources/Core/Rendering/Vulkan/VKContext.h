#pragma once
#include "Core/Rendering/Context.h"

namespace Pictura::Graphics::Vulkan
{
	class PICTURA_API VKContext final : public Context
	{
		void Init(bool Debug) override
		{
			GladVulkanContext* context = (GladVulkanContext*)malloc(sizeof(GladVulkanContext));
			if (!context) return;

			int version = gladLoadVulkanContext(context, *device, glfwGetProcAddress);

			SetPtr(context);
		}

		VkPhysicalDevice* device;
	};
}