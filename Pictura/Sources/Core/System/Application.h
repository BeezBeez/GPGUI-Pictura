#pragma once
#include "Core/Core.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventsArgs/StartupEventArgs.h"
#include "Widgets/Window/Window.h"
#include "Core/Rendering/Renderer.h"

using namespace Pictura::Graphics;
using namespace Pictura::Events;

namespace Pictura
{
	class PICTURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		Event<StartupEventArgs> ApplicationStart;
		virtual void OnApplicationStart(StartupEventArgs& e)
		{
			
		}

		Event<void> ApplicationClose;
		virtual void OnApplicationClose()
		{
			
		}

	private:
		Renderer::RendererType sRenderer;

	public:
		PVector<PString> Arguments;
		static Application* CurrentApplication;
		Renderer* CurrentRenderer;
		PVector<Widgets::Window*> WindowCollection;

	public:
		void SetRenderer(Renderer::RendererType RendererType, bool enableDebugMessages = false);
		Renderer::RendererType GetRendererType() const;
	};

	Application* InitApplication();
}
