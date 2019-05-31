#pragma once
#include "Core\Core.h"
#include "Core\Events\Event.h"
#include "Core\Events\EventsArgs\StartupEventArgs.h"
#include "Core\Debug\Log.h"

using namespace Pictura::Events;

namespace Pictura
{
	class PICTURA_API Application
	{
	public:
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

		Event<StartupEventArgs> ApplicationStart;
		virtual void OnApplicationStart(StartupEventArgs& e) {}

		Event<void> ApplicationClose;
		virtual void OnApplicationClose() {}

		virtual void Run() {
			StartupEventArgs e = StartupEventArgs();
			ApplicationStart(e);
		}
	private:
		Renderer sRenderer;
	public:
		void SetRenderer(Application::Renderer RendererType);
		Application::Renderer GetRenderer();
	};

	Application* InitApplication();
}
