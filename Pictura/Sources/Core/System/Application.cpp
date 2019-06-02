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
		sRenderer = Renderer::Null;
		SetRenderer(Renderer::OpenGL);
	}

	Application::~Application()
	{

	}

	void Application::SetRenderer(Application::Renderer RendererType)
	{
		sRenderer = RendererType;
	}

	Application::Renderer Application::GetRenderer() const
	{
		return sRenderer;
	}
}

