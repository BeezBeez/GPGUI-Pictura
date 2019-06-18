#pragma once
#if PLATFORM_WINDOWS == 1
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
			EnableStandardLayers();
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
		VkPhysicalDeviceProperties _physicalDeviceProperties = {};

		uint32_t _graphicsFamilyIndex = 0;

		PVector<const char*> instanceLayers;
		PVector<const char*> instanceExtensions;

		PVector<const char*> deviceLayers;
		PVector<const char*> deviceExtensions;

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
			instanceCreateInfo.enabledLayerCount = instanceLayers.size();
			instanceCreateInfo.enabledExtensionCount = instanceExtensions.size();
			instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
			instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

			CheckErrors(vkCreateInstance(&instanceCreateInfo, nullptr, &_instance));
		}

		void DestroyInstance()
		{
			vkDestroyInstance(_instance, nullptr);
			_instance = nullptr;
		}

		void InitDevice()
		{
			/* VULKAN PHYSICAL DEVICES ENUMERATION*/
			uint32_t gpuCount = 0;
			vkEnumeratePhysicalDevices(_instance, &gpuCount, nullptr);
			PVector<VkPhysicalDevice> gpuList(gpuCount);
			vkEnumeratePhysicalDevices(_instance, &gpuCount, gpuList.data());
			_gpu = gpuList[0];

			vkGetPhysicalDeviceProperties(_gpu, &_physicalDeviceProperties);
			if (ShowDebugMessage)
			{
				Debug::Log::Trace("A GPU Device was automatically selected :", "VULKAN");
				Debug::Log::Trace("		- GPU Name : " + PString(_physicalDeviceProperties.deviceName), "VULKAN");
				Debug::Log::Trace("		- GPU Device ID : " + Types::ToString(_physicalDeviceProperties.deviceID), "VULKAN");
				Debug::Log::Trace("		- GPU DriverVersion : " + Types::ToString(_physicalDeviceProperties.driverVersion), "VULKAN");
				Debug::Log::Trace("		- GPU Vendor ID : " + Types::ToString(_physicalDeviceProperties.vendorID), "VULKAN");
				Debug::Log::Trace("		- GPU Device Type : " + Types::ToString(_physicalDeviceProperties.deviceType), "VULKAN");
			}

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


			/*  VULKAN INSTANCE LAYERS ENUMERATION */
			uint32_t layerCount = 0;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
			PVector<VkLayerProperties> layerPropertyList(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, layerPropertyList.data());

			if (ShowDebugMessage)
			{
				Debug::Log::Trace("Instance layers : ", "VULKAN");
				for (auto layer : layerPropertyList)
				{
					Debug::Log::Trace("		- " + PString(layer.layerName) + " | DESCRIPTION : " + PString(layer.description), "VULKAN");
				}
			}

			/* VULKAN DEVICE LAYERS ENUMERATION */
			uint32_t deviceLayerCount = 0;
			vkEnumerateDeviceLayerProperties(_gpu, &deviceLayerCount, nullptr);
			PVector<VkLayerProperties> deviceLayerPropertyList(deviceLayerCount);
			vkEnumerateDeviceLayerProperties(_gpu, &deviceLayerCount, deviceLayerPropertyList.data());

			if (ShowDebugMessage)
			{
				Debug::Log::Trace("Device layers : ", "VULKAN");
				for (auto deviceLayer : deviceLayerPropertyList)
				{
					Debug::Log::Trace("		- " + PString(deviceLayer.layerName) + " | DESCRIPTION : " + PString(deviceLayer.description), "VULKAN");
				}
			}

			/* VULKAN DEVICE CREATION */
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
			deviceCreateInfo.enabledLayerCount = deviceLayers.size();
			deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
			deviceCreateInfo.ppEnabledLayerNames = deviceLayers.data();
			deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

			CheckErrors(vkCreateDevice(_gpu, &deviceCreateInfo, nullptr, &_device));

		}

		void DestroyDevice()
		{
			vkDestroyDevice(_device, nullptr);
			_device = nullptr;
		}

		void EnableStandardLayers()
		{
			instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
			instanceLayers.push_back("VK_LAYER_LUNARG_core_validation");
			instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

			deviceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
			deviceLayers.push_back("VK_LAYER_LUNARG_core_validation");

		}

		void CheckErrors(VkResult result)
		{
			if (result < 0)
			{
				switch (result)
				{
				case VK_ERROR_OUT_OF_HOST_MEMORY:
					Debug::Log::Error("VK_ERROR_OUT_OF_HOST_MEMORY");
					break;
				case VK_ERROR_OUT_OF_DEVICE_MEMORY:
					Debug::Log::Error("VK_ERROR_OUT_OF_DEVICE_MEMORY");
					break;
				case VK_ERROR_INITIALIZATION_FAILED:
					Debug::Log::Error("VK_ERROR_INITIALIZATION_FAILED");
					break;
				case VK_ERROR_DEVICE_LOST:
					Debug::Log::Error("VK_ERROR_DEVICE_LOST");
					break;
				case VK_ERROR_MEMORY_MAP_FAILED:
					Debug::Log::Error("VK_ERROR_MEMORY_MAP_FAILED");
					break;
				case VK_ERROR_LAYER_NOT_PRESENT:
					Debug::Log::Error("VK_ERROR_LAYER_NOT_PRESENT");
					break;
				case VK_ERROR_EXTENSION_NOT_PRESENT:
					Debug::Log::Error("VK_ERROR_EXTENSION_NOT_PRESENT");
					break;
				case VK_ERROR_FEATURE_NOT_PRESENT:
					Debug::Log::Error("VK_ERROR_FEATURE_NOT_PRESENT");
					break;
				case VK_ERROR_INCOMPATIBLE_DRIVER:
					Debug::Log::Error("VK_ERROR_INCOMPATIBLE_DRIVER");
					break;
				case VK_ERROR_TOO_MANY_OBJECTS:
					Debug::Log::Error("VK_ERROR_TOO_MANY_OBJECTS");
					break;
				case VK_ERROR_FORMAT_NOT_SUPPORTED:
					Debug::Log::Error("VK_ERROR_FORMAT_NOT_SUPPORTED");
					break;
				case VK_ERROR_SURFACE_LOST_KHR:
					Debug::Log::Error("VK_ERROR_SURFACE_LOST_KHR");
					break;
				case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
					Debug::Log::Error("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
					break;
				case VK_SUBOPTIMAL_KHR:
					Debug::Log::Error("VK_SUBOPTIMAL_KHR");
					break;
				case VK_ERROR_OUT_OF_DATE_KHR:
					Debug::Log::Error("VK_ERROR_OUT_OF_DATE_KHR");
					break;
				case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
					Debug::Log::Error("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
					break;
				case VK_ERROR_VALIDATION_FAILED_EXT:
					Debug::Log::Error("VK_ERROR_VALIDATION_FAILED_EXT");
					break;
				default:
					break;
				}
				throw RendererException("Vulkan runtime fatal error!");
			}
		}
	};
}
