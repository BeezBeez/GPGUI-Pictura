#pragma once
#include "Core/Core.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventsArgs/StartupEventArgs.h"
//#include "Core/Rendering/Vulkan/VKRenderer.h"
//#include "Widgets/Window/Window.h"

using namespace Pictura::Events;

namespace Pictura
{
	class PICTURA_API Application
	{
	public:
		enum class RendererType
		{
			Null,
			DirectX12,
			Vulkan
		};

	public:
		Application();
		virtual ~Application();

		Event<StartupEventArgs> ApplicationStart;
		virtual void OnApplicationStart(StartupEventArgs& e)
		{
			//Graphics::Vulkan::VKRenderer vkRenderer;
		}

		Event<void> ApplicationClose;
		virtual void OnApplicationClose()
		{
			
		}

	private:
		RendererType sRenderer;
		//PVector<Window> WindowCollection;

	public:
		PVector<PString> Arguments;
		static Application* CurrentApplication;
		static PString* CurrentRenderer;

	public:
		void SetRenderer(Application::RendererType RendererType);
		RendererType GetRenderer() const;
	};

	Application* InitApplication();
}
