﻿#include "PicturaPCH.h"
#include "VKCommandBuffer.h"
#include "VKRenderer.h"

namespace Pictura::Graphics::Vulkan
{
	VKCommandBuffer::VKCommandBuffer(VKRenderer* renderer, const VkCommandBufferLevel &bufferLevel)
	{
		vkr = renderer;
		m_vkCmdPool = CastTo<VKCommandPool*>(renderer->CommandPool)->GetVkCmdPool();

		if (m_vkCmdPool == nullptr)
		{
			throw RendererException("Creation of command buffer failed. No command pool was created before.");
		}

		VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = *m_vkCmdPool;
		commandBufferAllocateInfo.commandBufferCount = 1;
		commandBufferAllocateInfo.level = bufferLevel;
		vkr->CheckErrors(vkAllocateCommandBuffers(*vkr->GetDevice(), &commandBufferAllocateInfo, &_commandBuffer));

		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Info("Vulkan command buffer created!", "VULKAN");
		}
	}

	VKCommandBuffer::~VKCommandBuffer()
	{
		if (m_vkCmdPool == nullptr)
		{
			return;
		}

		vkFreeCommandBuffers(*vkr->GetDevice(), *m_vkCmdPool, 1, &_commandBuffer);
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

		
		VkSemaphoreCreateInfo signalSemaphoreCreateInfo = {};
		signalSemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		vkCreateSemaphore(*vkr->GetDevice(), &signalSemaphoreCreateInfo, nullptr, &signalSemaphore);


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
		if (isRunning)
		{
			End();
		}

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_commandBuffer;

		if (waitSemaphore != nullptr)
		{
			static VkPipelineStageFlags submitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			submitInfo.pWaitDstStageMask = &submitPipelineStages;
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = &waitSemaphore;
		}

		if (signalSemaphore != nullptr)
		{
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = &signalSemaphore;
		}

		if (_fence != nullptr)
		{
			vkr->CheckErrors(vkResetFences(*vkr->GetDevice(), 1, &_fence));
		}

		vkr->CheckErrors(vkQueueSubmit(*vkr->GetQueue(), 1, &submitInfo, _fence));

		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Trace("VkCommandBuffer -> SEND", "VULKAN");
		}
	}

	void VKCommandBuffer::SendAndWait()
	{
		if (isRunning)
		{
			End();
		}

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_commandBuffer;

		VkFenceCreateInfo fenceCreateInfo = {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		vkr->CheckErrors(vkCreateFence(*vkr->GetDevice(), &fenceCreateInfo, nullptr, &_fence));

		vkr->CheckErrors(vkResetFences(*vkr->GetDevice(), 1, &_fence));
		vkr->CheckErrors(vkQueueSubmit(*vkr->GetQueue(), 1, &submitInfo, _fence));
		vkr->CheckErrors(vkWaitForFences(*vkr->GetDevice(), 1, &_fence, true, UINT64_MAXVALUE));

		vkDestroyFence(*vkr->GetDevice(), _fence, nullptr);

		if (vkr->ShowDebugMessage)
		{
			Debug::Log::Trace("VkCommandBuffer -> SEND_AND_WAIT", "VULKAN");
		}
	}
}
