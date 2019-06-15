#include "PicturaPCH.h"
#include "Application.h"
#include "Runtime.h"
#include "Core/Rendering/Vulkan/VKRenderer.h"
#include "Core/Rendering/D3D12/D3D12Renderer.h"

namespace Pictura
{
	Application* Application::CurrentApplication = nullptr;

	Application::Application()
	{
		Runtime::Assert(CurrentApplication, "Application was already initialized");
		CurrentApplication = this;
		ApplicationStart += EventHandler::Bind(&Application::OnApplicationStart, this);
		ApplicationClose += EventHandler::Bind(&Application::OnApplicationClose, this);
		sRenderer = Renderer::RendererType::Null;
	}

	Application::~Application()
	{

	}

	void Application::SetRenderer(Renderer::RendererType RendererType)
	{
		if (CurrentRenderer != nullptr)
		{
			Debug::Log::Trace("Destroying previous renderer...","APPLICATION");
			CurrentRenderer->Destroy();
			delete CurrentRenderer;
		}

		switch (RendererType)
		{
		case Renderer::RendererType::Null:
			Debug::Log::Trace("Null renderer created.");
			break;

		case Renderer::RendererType::DirectX12:
			Debug::Log::Trace("Creating a DirectX 12 renderer...", "APPLICATION");
			CurrentRenderer = new D3D12::D3D12Renderer();
			break;

		case Renderer::RendererType::Vulkan:
			Debug::Log::Trace("Creating a Vulkan renderer...", "APPLICATION");
			CurrentRenderer = new Vulkan::VKRenderer();
			break;

		default: 
			break;
		}

		if (CurrentRenderer != nullptr)
		{
			CurrentRenderer->Init();
		}

		sRenderer = RendererType;
	}

	Renderer::RendererType Application::GetRendererType() const
	{
		return sRenderer;
	}
}

