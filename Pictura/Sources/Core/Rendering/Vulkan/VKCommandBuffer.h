#pragma once
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

		VkCommandBuffer* GetVkCmdBuffer() { return &_commandBuffer; }

	private:
		VkCommandPool* m_vkCmdPool = nullptr;
		VkCommandBuffer _commandBuffer = nullptr;
		VkFence _fence = nullptr;

		VkSemaphore waitSemaphore = {};
		VkSemaphore signalSemaphore = {};

		VKRenderer* vkr = nullptr;
		bool isRunning = false;
	};
}
