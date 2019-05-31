#include "PicturaPCH.h"
#include "Application.h"

namespace Pictura
{
	Application::Application()
	{
		Runtime::CurrentApplication = this;
		ApplicationStart += EventHandler::Bind(&Application::OnApplicationStart, this);
		ApplicationClose += EventHandler::Bind(&Application::OnApplicationClose, this);
	}

	Application::~Application()
	{
		ApplicationClose();
	}

	void Application::SetRenderer(Application::Renderer RendererType)
	{
		sRenderer = RendererType;
	}

	Application::Renderer Application::GetRenderer()
	{
		return sRenderer;
	}
}

