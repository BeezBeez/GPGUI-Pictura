#include "PicturaPCH.h"
#include "Application.h"
#include "Runtime.h"
#include "Core/Rendering/Vulkan/VKRenderer.h"

namespace Pictura
{
	Application* Application::CurrentApplication = nullptr;

	Application::Application()
	{
		Runtime::Assert(CurrentApplication, "Application was already initialized");

		MainWindow = nullptr;
		CurrentApplication = this;
		CurrentRenderer = nullptr;
		mRenderer = Renderer::RendererType::Null;
		ApplicationCloseBehavior = CloseBehavior::OnRequestExit;
	}

	Application::~Application()
	{

	}

	void Application::SetRenderer(Renderer::RendererType rendererType, bool enableDebugMessages)
	{
		if (rendererType != Renderer::RendererType::Null && GetRendererType() != Renderer::RendererType::Null)
		{
			throw RendererException("You can't select a second time the application renderer at runtime !");
			Runtime::ForceExitApplication();
		}

		if (CurrentRenderer != nullptr)
		{
			Debug::Log::Trace("Destroying previous renderer...","APPLICATION");
			CurrentRenderer->Destroy();
			delete CurrentRenderer;
		}

		switch (rendererType)
		{
			case Renderer::RendererType::Null:
				break;
			case Renderer::RendererType::Vulkan:
				Debug::Log::Trace("Creating a Vulkan renderer...", "APPLICATION");
				CurrentRenderer = new Vulkan::VKRenderer();
				break;
			case Renderer::RendererType::OpenGL:
				Debug::Log::Trace("Creating a OpenGL renderer...", "APPLICATION");
				CurrentRenderer = new OpenGL::GLRenderer(4, 3);
				break;
			default:
				throw RendererException("Failed to instantiate a non implemented renderer...");
				break;
		}

		if (CurrentRenderer != nullptr)
		{
			CurrentRenderer->ShowDebugMessage = enableDebugMessages;
			CurrentRenderer->Init();
		}

		mRenderer = rendererType;
	}

	Renderer::RendererType Application::GetRendererType() const
	{
		return mRenderer;
	}

	void Application::Run(StartupEventArgs e)
	{
		this->OnApplicationStart(e);
		while (!isQuitting) {}
		this->OnApplicationClose();
		ApplicationThread.reset();
	}

	void Application::Exit()
	{
		if (!isQuitting)
		{
			ApplicationCloseBehavior = CloseBehavior::OnRequestExit;

			isQuitting = true;
		}
	}
}

