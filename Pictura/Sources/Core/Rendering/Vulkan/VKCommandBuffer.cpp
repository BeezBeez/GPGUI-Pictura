#include "PicturaPCH.h"
#include "VKCommandBuffer.h"
#include "VKRenderer.h"

namespace Pictura::Graphics::Vulkan
{
	VKCommandBuffer::VKCommandBuffer(VKRenderer* renderer, const VkCommandBufferLevel &bufferLevel)
	{
		vkr = renderer;
		m_vkCmdPool = CastTo<VKCommandPool*>(renderer->CommandPool)->GetVkCmdPool();

		VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = *m_vkCmdPool;
		commandBufferAllocateInfo.commandBufferCount = 1;
		commandBufferAllocateInfo.level = bufferLevel;
		vkr->CheckErrors(vkAllocateCommandBuffers(vkr->GetDevice(), &commandBufferAllocateInfo, &_commandBuffer));

		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Info("Vulkan command buffer created!", "VULKAN");
		}
	}

	VKCommandBuffer::~VKCommandBuffer()
	{
		vkFreeCommandBuffers(vkr->GetDevice(), *m_vkCmdPool, 1, &_commandBuffer);
	}

	void VKCommandBuffer::Begin()
	{
		if (isRunning)
		{
			return;
		}

		VkCommandBufferBeginInfo commandBufferBeginInfo{};
		commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		vkr->CheckErrors(vkBeginCommandBuffer(_commandBuffer, &commandBufferBeginInfo));
		isRunning = true;

		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Trace("VkCommandBuffer -> BEGIN", "VULKAN");
		}
	}

	void VKCommandBuffer::End()
	{
		if (!isRunning)
		{
			return;
		}

		vkr->CheckErrors(vkEndCommandBuffer(_commandBuffer));
		isRunning = false;

		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Trace("VkCommandBuffer -> END", "VULKAN");
		}
	}

	void VKCommandBuffer::Send()
	{
		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Trace("VkCommandBuffer -> SEND", "VULKAN");
		}
	}

	void VKCommandBuffer::SendAndWait()
	{
		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Trace("VkCommandBuffer -> SEND_AND_WAIT", "VULKAN");
		}
	}
}
