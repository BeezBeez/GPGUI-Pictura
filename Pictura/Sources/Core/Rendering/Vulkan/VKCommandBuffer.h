#pragma once
#include <vulkan/vulkan.h>
#include "Core/Rendering/CommandBuffer.h"
namespace Pictura::Graphics::Vulkan
{
	class VKRenderer;
	class PICTURA_API VKCommandBuffer final : public CommandBuffer
	{
	public:
		VKCommandBuffer(VKRenderer* renderer, const VkCommandBufferLevel &bufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		~VKCommandBuffer();


		void Begin() override;
		void End() override;
		void Send() override;
		void SendAndWait() override;

	private:
		VkCommandPool* m_vkCmdPool = nullptr;
		VkCommandBuffer _commandBuffer = nullptr;

		VKRenderer* vkr = nullptr;
		bool isRunning = false;
	};
}
