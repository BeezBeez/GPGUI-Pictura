#pragma once
#if PLATFORM_WINDOWS ==1
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#if PLATFORM_LINUX == 1

#endif

#if PLATFORM_OSX == 1
#define VK_USE_PLATFORM_MACOS_MVK
#endif
#include <vulkan/vulkan.h>
#include "Core/Rendering/Renderer.h"
#include "Core/Exceptions/RendererException.h"

namespace Pictura::Graphics::Vulkan
{
	class PICTURA_API VKRenderer final : public Renderer
	{
	public:
		VKRenderer()
		{
			
		}
		
		virtual ~VKRenderer()
		{
			
		}

		void Init() override
		{
			InitInstance();
			InitDevice();
			Debug::Log::Success("Vulkan renderer creation completed !", "RENDERER");
		}

		void Destroy() override
		{
			DestroyInstance();
			DestroyDevice();
		}

	private:
		VkInstance _instance = nullptr;
		VkDevice   _device = nullptr;
		VkPhysicalDevice _gpu = nullptr;

		uint32_t _graphicsFamilyIndex = 0;

	private:
		void InitInstance()
		{
			VkApplicationInfo applicationInfo{};
			applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			applicationInfo.apiVersion = VK_API_VERSION_1_1;
			applicationInfo.pApplicationName = "Vulkan pictura renderer";

			VkInstanceCreateInfo instanceCreateInfo{};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &applicationInfo;

			auto err = vkCreateInstance(&instanceCreateInfo, nullptr, &_instance);
			if (err != VK_SUCCESS)
			{
				throw RendererException("Vulkan instance creation failed [error code : " + Types::ToString(Types::ToUnderlying(err)) + "]");
			}
			Debug::Log::Info("Vulkan instance created","RENDERER");
		}

		void DestroyInstance()
		{
			vkDestroyInstance(_instance, nullptr);
			_instance = nullptr;
		}

		void InitDevice()
		{
			uint32_t gpuCount = 0;
			vkEnumeratePhysicalDevices(_instance, &gpuCount, nullptr);
			PVector<VkPhysicalDevice> gpuList(gpuCount);
			vkEnumeratePhysicalDevices(_instance, &gpuCount, gpuList.data());
			_gpu = gpuList[0];

			VkPhysicalDeviceProperties physicalDeviceProperties{};
			vkGetPhysicalDeviceProperties(_gpu, &physicalDeviceProperties);
			Debug::Log::Trace("A GPU Device was automatically selected :");
			Debug::Log::Trace("		- GPU Name : " + PString(physicalDeviceProperties.deviceName));
			Debug::Log::Trace("		- GPU Device ID : " + Types::ToString(physicalDeviceProperties.deviceID));
			Debug::Log::Trace("		- GPU DriverVersion : " + Types::ToString(physicalDeviceProperties.driverVersion));
			Debug::Log::Trace("		- GPU Vendor ID : " + Types::ToString(physicalDeviceProperties.vendorID));
			Debug::Log::Trace("		- GPU Device Type : " + Types::ToString(physicalDeviceProperties.deviceType));

			uint32_t familyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &familyCount, nullptr);
			PVector<VkQueueFamilyProperties> familyPropertyList(familyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(_gpu, &familyCount, familyPropertyList.data());

			bool foundGraphicsBit = false;
			for (uint32_t i = 0; i < familyCount; ++i)
			{
				if (familyPropertyList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					foundGraphicsBit = true;
					_graphicsFamilyIndex = i;
				}
			}

			if (!foundGraphicsBit)
			{
				throw RendererException("Vulkan device creation failed : Queue family supporting graphics not found.");
				return;
			}

			float queuePriorities[] { 1.0f };
			VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
			deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueCreateInfo.queueFamilyIndex = _graphicsFamilyIndex;
			deviceQueueCreateInfo.queueCount = 1;
			deviceQueueCreateInfo.pQueuePriorities = queuePriorities;

			VkDeviceCreateInfo deviceCreateInfo{};
			deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			deviceCreateInfo.queueCreateInfoCount = 1;
			deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;

			auto err = vkCreateDevice(_gpu, &deviceCreateInfo, nullptr,&_device);
			if (err != VK_SUCCESS)
			{
				throw RendererException("Vulkan device creation failed [error code :" + Types::ToString(Types::ToUnderlying(err)) + "]");
			}

			Debug::Log::Info("Vulkan device created", "RENDERER");
		}

		void DestroyDevice()
		{
			vkDestroyDevice(_device, nullptr);
			_device = nullptr;
		}

	};
}
