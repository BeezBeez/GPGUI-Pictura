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
		ApplicationStart += EventHandler::Bind(&Application::OnApplicationStart, this);
		ApplicationClose += EventHandler::Bind(&Application::OnApplicationClose, this);
		mRenderer = Renderer::RendererType::Null;
		ApplicationCloseBehavior = CloseBehavior::OnRequestExit;
	}

	Application::~Application()
	{
		for (auto &window : WindowCollection)
		{
			window->Close();
		}
	}

	void Application::SetRenderer(Renderer::RendererType rendererType, bool enableDebugMessages)
	{
		if (rendererType != Renderer::RendererType::Null && GetRendererType() != Renderer::RendererType::Null)
		{
			throw RendererException("You can't select a second time the application renderer at runtime !");
			Runtime::ForceExitApplication();
		}


		for (Widgets::Window* window : WindowCollection)
		{
			window->ResetWindow(true);
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
				Debug::Log::Trace("Null renderer created.");
				break;

			case Renderer::RendererType::Vulkan:
				Debug::Log::Trace("Creating a Vulkan renderer...", "APPLICATION");
				CurrentRenderer = new Vulkan::VKRenderer();
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

		for (Widgets::Window* window : WindowCollection)
		{
			window->ResetWindow(true);
		}

		mRenderer = rendererType;
	}

	Renderer::RendererType Application::GetRendererType() const
	{
		return mRenderer;
	}

	void Application::Exit()
	{
		if (!isQuitting)
		{
			isQuitting = true;

			ApplicationCloseBehavior = CloseBehavior::OnRequestExit;
			Debug::Log::Info("Closing all windows before exiting application...");
			while (WindowCollection.size() > 0)
			{
				WindowCollection[0]->Close();
			}
			Debug::Log::Success("All windows were closed !");
		}
	}
}

