#pragma once

#include "Core/Rendering/Renderer.h"
#include "VKCommandPool.h"
#include "VKCommandBuffer.h"

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

			CreateCommandPool();
			CreateCommandBuffer();
			Debug::Log::Success("Vulkan renderer creation completed !", "RENDERER");

			//DemoVulkan();
		}

		void Destroy() override
		{
			if (ShowDebugMessage)
			{
				Debug::Log::Info("Send VKDevice destroy request...", "VULKAN");
			}

			DestroyInstance();
			DestroyDevice();
		}

		void CreateCommandPool() override
		{
			CommandPool = new VKCommandPool(this);
		}

		void CreateCommandBuffer() override
		{
			CommandBuffer = new VKCommandBuffer(this);
		}

	public:
		VkInstance* GetInstance() { return &_instance; }
		VkDevice* GetDevice() { return &_device; }
		VkPhysicalDevice* GetPhysicalDevice() { return &_gpu; }
		VkQueue* GetQueue() { return &_queue; }

		uint32_t GetGraphicsFamilyIndex() const { return _graphicsFamilyIndex; }

		void CheckErrors(VkResult result)
		{
			if (result != VK_SUCCESS)
			{
				bool throwAtEnd = true;
				switch (result)
				{
				case VK_TIMEOUT:
					Debug::Log::Error("Vulkan wait operation has not completed in the specified time!");
					break;
				case VK_ERROR_OUT_OF_HOST_MEMORY:
					Debug::Log::Error("Vulkan host memory allocation has failed!");
					break;
				case VK_ERROR_OUT_OF_DEVICE_MEMORY:
					Debug::Log::Error("Vulkan device memory allocation has failed!");
					break;
				case VK_ERROR_INITIALIZATION_FAILED:
					Debug::Log::Error("Vulkan initialization failed!");
					break;
				case VK_ERROR_DEVICE_LOST:
					Debug::Log::Error("Vulkan logical or physical device has been lost!");
					break;
				case VK_ERROR_MEMORY_MAP_FAILED:
					Debug::Log::Error("Vulkan error, memory map failed!");
					break;
				case VK_ERROR_LAYER_NOT_PRESENT:
					Debug::Log::Error("Vulkan layer not found!");
					break;
				case VK_ERROR_EXTENSION_NOT_PRESENT:
					Debug::Log::Error("Vulkan extension not found or not supported!");
					break;
				case VK_ERROR_FEATURE_NOT_PRESENT:
					Debug::Log::Error("Vulkan feature not available or not supported!");
					break;
				case VK_ERROR_INCOMPATIBLE_DRIVER:
					Debug::Log::Error("Vulkan not supported GPU drivers!");
					break;
				case VK_ERROR_TOO_MANY_OBJECTS:
					Debug::Log::Error("Vulkan error, too many objects of the type have already been created!");
					break;
				case VK_ERROR_FORMAT_NOT_SUPPORTED:
					Debug::Log::Error("Vulkan format not supported");
					break;
				case VK_ERROR_SURFACE_LOST_KHR:
					Debug::Log::Error("Vulkan surface is no longer available!");
					break;
				case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
					Debug::Log::Error("Vulkan error, the requested window is already in use by Vulkan or another API in a manner which prevents it from being used again.!");
					break;
				case VK_ERROR_OUT_OF_DATE_KHR:
					Debug::Log::Error("Vulkan outdated KHR");
					break;
				case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
					Debug::Log::Error("Vulkan error, not supported display!");
					break;
				case VK_ERROR_VALIDATION_FAILED_EXT:
					Debug::Log::Error("Vulkan error, validation failed!");
					break;
				case VK_NOT_READY:
					Debug::Log::Error("Vulkan error, a fence or query has not yet completed!");
					break;
				case VK_INCOMPLETE:
					Debug::Log::Error("Vulkan error, a return array was too small for the result!");
					break;
				case VK_ERROR_FRAGMENTED_POOL:
					Debug::Log::Error("Vulkan error, pool allocation has failed due to fragmentation of the pool's memory!");
					break;
				case VK_ERROR_OUT_OF_POOL_MEMORY:
					Debug::Log::Error("Vulkan error, a pool memory allocation has failed!");
					break;
				case VK_ERROR_INVALID_EXTERNAL_HANDLE:
					Debug::Log::Error("Vulkan invalid external handle!");
					break;
				case VK_ERROR_INVALID_SHADER_NV:
					Debug::Log::Error("Vulkan error, invalid shader!");
					break;
				case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
					Debug::Log::Error("Vulkan error, invalid DRM FORMAT");
					break;
				case VK_ERROR_FRAGMENTATION_EXT:
					Debug::Log::Error("Vulkan error, a descriptor pool creation has failed due to fragmentation!");
					break;
				case VK_ERROR_INVALID_DEVICE_ADDRESS_EXT:
					Debug::Log::Error("Vulkan buffer creation failed because the requested address is not available!");
					break;
				case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
					Debug::Log::Error("Vulkan error, an operation on a swapchain created with VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT failed as it did not have exlusive full-screen access. This may occur due to implementation-dependent reasons, outside of the application's control.");
					break;
				default:
					Debug::Log::Warning("Unknown vulkan error occured!");
					Debug::Log::Warning("The renderer will not be killed, but if you see this message frequently, then consider reviewing your program's code");
					throwAtEnd = false;
					break;
				}

				if(throwAtEnd)
				{
					throw RendererException("Vulkan runtime fatal error!");
				}
			}
		}

	private:
		VkInstance _instance = nullptr;
		VkDevice   _device = nullptr;
		VkPhysicalDevice _gpu = nullptr;
		VkQueue _queue = nullptr;
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
			applicationInfo.pApplicationName = "Vulkan Pictura renderer";

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

			vkGetDeviceQueue(_device, _graphicsFamilyIndex, 0, &_queue);
		}

		void DestroyDevice()
		{
			vkDeviceWaitIdle(_device);
			
			vkDestroyDevice(_device, nullptr);
			_device = nullptr;
		}

		void EnableStandardLayers()
		{
			instanceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
			instanceLayers.push_back("VK_LAYER_LUNARG_core_validation");
			
			instanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
			instanceExtensions.push_back(SURFACE_EXTENSION_NAME);

			deviceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
			deviceLayers.push_back("VK_LAYER_LUNARG_core_validation");
		}

		void DemoVulkan()
		{
			CommandBuffer->Begin();

			VkViewport viewport = {
				0,
				0,
				1280,
				720,
				0.0f,
				1.0f
			};

			vkCmdSetViewport(*CastTo<VKCommandBuffer*>(CommandBuffer)->GetVkCmdBuffer(), 0, 1, &viewport);
			
			CommandBuffer->End();
			CommandBuffer->Send();
		}
	};
}
