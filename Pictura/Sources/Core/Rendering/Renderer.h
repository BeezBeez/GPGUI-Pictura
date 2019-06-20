#pragma once
#include "Core/Core.h"
#include "Core/Debug/Log.h"
#include "CommandBuffer.h"
#include "Core\Exceptions\RendererException.h"

namespace Pictura::Graphics
{
	class PICTURA_API Renderer
	{
	public:
		enum class RendererType
		{
			Null,
			DirectX12,
			Vulkan
		};

	public:
		virtual ~Renderer()
		{
			
		}

	public:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void CreateCommandPool() = 0;
		virtual void CreateCommandBuffer() = 0;
	
	public:
		bool ShowDebugMessage = false;

	public:
		CommandPool* CommandPool = nullptr;
		CommandBuffer* CommandBuffer = nullptr;

	};
}
