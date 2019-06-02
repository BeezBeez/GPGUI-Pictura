#pragma once
#include "Core/Core.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventsArgs/StartupEventArgs.h"
#include "Widgets/Window/Window.h"

using namespace Pictura::Widgets;
using namespace Pictura::Events;

namespace Pictura
{
	class PICTURA_API Application
	{
	public:
		enum class Renderer
		{
			Null,
			DirectX12,
			Vulkan
		};

	public:
		Application();
		virtual ~Application();

		Event<StartupEventArgs> ApplicationStart;
		virtual void OnApplicationStart(StartupEventArgs& e) {}

		Event<void> ApplicationClose;
		virtual void OnApplicationClose() {}

	private:
		Renderer sRenderer;
		PVector<Window> WindowCollection;

	public:
		PVector<PString> Arguments;
		static Application* CurrentApplication;
		static PString* CurrentRenderer;

	public:
		void SetRenderer(Application::Renderer RendererType);
		Application::Renderer GetRenderer() const;
	};

	Application* InitApplication();
}
