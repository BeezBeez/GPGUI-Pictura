#include "PicturaPCH.h"
#include "Window.h"
#include "Core/CoreException.h"
#include "Core/System/Application.h"
#include <Core\System\Runtime.h>

namespace Pictura::Widgets
{
	Window::Window()
	{
		Shown += EventHandler::Bind(&Window::OnShown, this);
		Closed += EventHandler::Bind(&Window::OnClosed, this);
		GotFocus += EventHandler::Bind(&Window::OnGotFocus, this);
		Updated += EventHandler::Bind(&Window::OnUpdate, this);
		Reset += EventHandler::Bind(&Window::OnReset, this);

		windowThread = nullptr;

		Size.Width = 0;
		Size.Height = 0;
	}

	Window::~Window()
	{
		if (!isClosing)
		{
			Close();
			auto app = Application::CurrentApplication;

			if (app->MainWindow == this && app->ApplicationCloseBehavior == Application::CloseBehavior::OnMainWindowClose)
			{
				app->Exit();
			}

			if (app->WindowCollection.size() == 1 && app->ApplicationCloseBehavior == Application::CloseBehavior::OnLastWindowClose)
			{
				app->Exit();
			}
		}
	}

	void Window::Show()
	{
		windowThread = Types::MakeUnique<Thread>(&Window::DisplayWindow, this);
		Application::CurrentApplication->WindowCollection.push_back(this);
	}

	void Window::Update()
	{
		while (isOnScreen)
		{
			RenderWindow();
			Updated();
		}
	}

	void Window::ResetWindow(bool finalPhase)
	{
		if (!finalPhase)
		{
			DestroySurface();
		}
		else
		{
			InitSurface();
			Reset();
		}
	}

	void Window::InitSurface()
	{
		BindSurface();

		switch (Application::CurrentApplication->GetRendererType())
		{
			case Renderer::RendererType::Vulkan:
			{
				auto VKRendererRef = ReinterpretCastTo<Vulkan::VKRenderer*>(Application::CurrentApplication->CurrentRenderer);
				auto gpu = *VKRendererRef->GetPhysicalDevice();

				VkBool32 WSI_Supported = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(gpu, VKRendererRef->GetGraphicsFamilyIndex(), vkSurface, &WSI_Supported);
				if (!WSI_Supported)
				{
					throw RendererException("The operating system doesn't support Window Surface Integration");
					Runtime::ForceExitApplication();
				}

				vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, vkSurface, &vkSurfaceCapabilities);

				uint32 formatCount = 0;
				vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, vkSurface, &formatCount, nullptr);
				if (formatCount == 0)
				{
					throw RendererException("Surface formats are missings...");
					Runtime::ForceExitApplication();
				}

				PVector<VkSurfaceFormatKHR> formats(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, vkSurface, &formatCount, formats.data());
				if (formats[0].format == VK_FORMAT_UNDEFINED)
				{
					vkSurfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
					vkSurfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
				}
				else
				{
					vkSurfaceFormat = formats[0];
				}

				break;
			}
			case Renderer::RendererType::DirectX12:
				throw RendererException("D3D12 Surface was not implemented yet !");
				break;
			default:
				break;
		}
	}

	void Window::Close()
	{
		if (isOnScreen) {
			Types::Vector::RemoveElement(Application::CurrentApplication->WindowCollection, this);
			isClosing = true;
			RemoveWindow();
			Closed();
			isOnScreen = false;
		}
	}

	void Window::DestroySurface()
	{
		auto VKRendererRef = ReinterpretCastTo<Vulkan::VKRenderer*>(Application::CurrentApplication->CurrentRenderer);
		vkDestroySurfaceKHR(*VKRendererRef->GetInstance(), vkSurface, nullptr);
	}
}
