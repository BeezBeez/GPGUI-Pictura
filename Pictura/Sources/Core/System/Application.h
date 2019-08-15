#pragma once
#include "Core/Core.h"
#include "Core/Events/Event.h"
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
			ApplicationStart(e);
		}

		Event<void> ApplicationClose;
		virtual void OnApplicationClose()
		{
			ApplicationClose();
		}

	private:
		Renderer::RendererType mRenderer;

	public:
		PVector<PString> Arguments;
		Application::CloseBehavior ApplicationCloseBehavior;

		static Application* CurrentApplication;
		Renderer* CurrentRenderer;

		Widgets::Window* MainWindow;
		PList<Widgets::Window*> WindowCollection;

		void Run(StartupEventArgs e);
		PUniquePtr<Thread> ApplicationThread;
	public:
		void SetRenderer(Renderer::RendererType rendererType, bool enableDebugMessages = false);
		Renderer::RendererType GetRendererType() const;
		void Exit();

		void Init(StartupEventArgs& e)
		{
			this->ApplicationThread.reset(new Thread(&Application::Run, this, e));
		}
	public:
		static bool IsGLRenderer()
		{
			return DynamicCastTo<OpenGL::GLRenderer*>(Application::CurrentApplication->CurrentRenderer) != nullptr;
		}

		static bool IsVKRenderer()
		{
			return DynamicCastTo<Vulkan::VKRenderer*>(Application::CurrentApplication->CurrentRenderer) != nullptr;
		}

		static OpenGL::GLRenderer* GetOpenGLRenderer()
		{
			return CastTo<OpenGL::GLRenderer*>(Application::CurrentApplication->CurrentRenderer);
		}

		static Vulkan::VKRenderer* GetVulkanRenderer()
		{
			return CastTo<Vulkan::VKRenderer*>(Application::CurrentApplication->CurrentRenderer);
		}

	private:
		bool isQuitting = false;

	};

	Application* InitApplication();
}