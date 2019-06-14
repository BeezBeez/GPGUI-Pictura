#include "PicturaPCH.h"
#include "Application.h"
#include "Runtime.h"

namespace Pictura
{
	Application* Application::CurrentApplication = nullptr;

	Application::Application()
	{
		Runtime::Assert(!CurrentApplication, "Application was already initialized");
		CurrentApplication = this;
		ApplicationStart += EventHandler::Bind(&Application::OnApplicationStart, this);
		ApplicationClose += EventHandler::Bind(&Application::OnApplicationClose, this);
		sRenderer = RendererType::Null;
		SetRenderer(RendererType::Vulkan);
	}

	Application::~Application()
	{

	}

	void Application::SetRenderer(Application::RendererType RendererType)
	{
		sRenderer = RendererType;
	}

	Application::RendererType Application::GetRenderer() const
	{
		return sRenderer;
	}
}

