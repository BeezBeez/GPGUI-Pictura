#pragma once
#include "Core/Core.h"
#include "Graphics/Color.h"
#include "Maths/Position.h"
#include "Maths/Size.h"
#include "Core/Debug/Log.h"
#include "CommandBuffer.h"
#include "Core/Exceptions/RendererException.h"

namespace Pictura::Graphics
{
	class PICTURA_API Renderer
	{
	public:
		enum class RendererType
		{
			Null,
			OpenGL,
			Vulkan
		};

	public:
		virtual ~Renderer() { }

	public:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void CreateCommandPool() = 0;
		virtual void CreateCommandBuffer() = 0;

	public:
		virtual void SwapBuffers() = 0;
		virtual void ClearColor(Color color) = 0;
		virtual void CreateViewport(Maths::PPosition position, Maths::PSize size) = 0;

	public:
		bool ShowDebugMessage = false;

	public:
		CommandPool* CommandPool = nullptr;
		CommandBuffer* CommandBuffer = nullptr;

	};
}
