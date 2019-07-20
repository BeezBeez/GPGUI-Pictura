#include "PicturaPCH.h"
#include "Window.h"
#include "Core/CoreException.h"
#include "Core/System/Application.h"
#include "Core/System/Runtime.h"

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
		auto app = Application::CurrentApplication;
		if (app->MainWindow == this && app->ApplicationCloseBehavior == Application::CloseBehavior::OnMainWindowClose)
		{
			Debug::Log::Trace("Main window was closed, exiting application...");
			app->Exit();
		}

		if (app->WindowCollection.size() == 1 && app->ApplicationCloseBehavior == Application::CloseBehavior::OnLastWindowClose)
		{
			Debug::Log::Trace("Last window was closed, exiting application...");
			app->Exit();
		}
	}

	void Window::Update()
	{
		while (isOnScreen)
		{
			if (IsWindowVisible(win32Window)) //TODO : Make platform independent.
			{
				Debug::Log::Info("COUCOU");
				RenderWindow();
				Updated();
			}
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
			default:
				break;
		}
	}

	void Window::Close()
	{
		if (isOnScreen && !isClosing) {
			isClosing = true;
			RemoveWindow();
			Closed();
			Types::Vector::RemoveElement(Application::CurrentApplication->WindowCollection, this);
			delete this;
		}
	}

	void Window::DestroySurface()
	{
		auto VKRendererRef = ReinterpretCastTo<Vulkan::VKRenderer*>(Application::CurrentApplication->CurrentRenderer);
		vkDestroySurfaceKHR(*VKRendererRef->GetInstance(), vkSurface, nullptr);
	}
}
