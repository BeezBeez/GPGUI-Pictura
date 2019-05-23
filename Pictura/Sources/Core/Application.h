#pragma once
#include "Core\Debug\Log.h"

namespace Pictura
{
	class PICTURA_API Application
	{
		enum class Renderer
		{
			OpenGL,
			DirectX11,
			DirectX12,
			Vulkan
		};

	public:
		Application();
		~Application();

		virtual void Run() {
			Debug::Log::Trace("Application init!");
		}
	private:
		Renderer sRenderer;
	public:
		void SetRenderer(Application::Renderer RendererType);

	};
}
