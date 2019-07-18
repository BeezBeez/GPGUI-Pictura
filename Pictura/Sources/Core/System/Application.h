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
		enum class CloseBehavior
		{
			OnMainWindowClose,
			OnLastWindowClose,
			OnRequestExit
		};

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
		Renderer::RendererType mRenderer;

	public:
		PVector<PString> Arguments;
		Application::CloseBehavior ApplicationCloseBehavior;

		static Application* CurrentApplication;
		Renderer* CurrentRenderer;

		Widgets::Window* MainWindow;
		PVector<Widgets::Window*> WindowCollection;

	public:
		void SetRenderer(Renderer::RendererType rendererType, bool enableDebugMessages = false);
		Renderer::RendererType GetRendererType() const;
		void Exit();
	private:
		bool isQuitting = false;

	};

	Application* InitApplication();
}