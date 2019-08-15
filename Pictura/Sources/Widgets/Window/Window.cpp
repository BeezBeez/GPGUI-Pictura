#include "Window.h"
#include "Core/System/Application.h"

namespace Pictura::Widgets
{
	Window::Window()
	{
		wndThread = Types::MakeUnique<Thread>(&Window::InitThread, this);
		Thread::LockThread();
	}

	Window::~Window()
	{
		//free(wndContext);
		wndThread.reset();
		
		switch (Application::CurrentApplication->ApplicationCloseBehavior)
		{
			case Application::CloseBehavior::OnLastWindowClose:
			{
				if (Application::CurrentApplication->WindowCollection.size() == 0)
				{
					Application::CurrentApplication->Exit();
				}
				break;
			}
			case Application::CloseBehavior::OnMainWindowClose:
			{
				if (Application::CurrentApplication->MainWindow == this)
				{
					Application::CurrentApplication->Exit();
				}
				break;
			}
			default:
				break;
		}
	}

	void Window::UpdateWindow()
	{
		bool isOpenGL = Application::IsGLRenderer();
		bool isVulkan = Application::IsVKRenderer();

		while (!glfwWindowShouldClose(WindowHandle))
		{
			glfwPollEvents();
			if (GetWidgetVisibility() == Visibility::Visible)
			{
				if (isOpenGL) {
					glfwMakeContextCurrent(WindowHandle);
				}

				Update();
				Render();

				if (isOpenGL) {
					glfwSwapBuffers(WindowHandle);
				}
			}
		}
		
		glfwDestroyWindow(WindowHandle);
		delete this;
	}

	void Window::Show()
	{
		SetWidgetVisibility(Visibility::Visible);
		OnShow();
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(WindowHandle, GLFW_TRUE);
		Types::Lists::RemoveElement(Application::CurrentApplication->WindowCollection, this);
		OnClose();
	}

	void Window::AddWidget(Widget* widget)
	{
		Children.push_back(widget);
	}

	void Window::RemoveWidget(Widget* widget)
	{
		Types::Vectors::RemoveElement<Widget*>(Children, widget);
		delete widget;
	}

	void Window::InitThread()
	{
		WindowHandle = InitWindow();

		switch (Application::CurrentApplication->GetRendererType())
		{
			case Renderer::RendererType::OpenGL:
			{
				glfwMakeContextCurrent(WindowHandle);
				Application::GetOpenGLRenderer()->CreateViewport(PPosition(0, 0), PSize(GetSize().Width, GetSize().Height));
				break;
			}
			case Renderer::RendererType::Vulkan:
			{
				Application::GetVulkanRenderer()->CheckErrors(glfwCreateWindowSurface(*Application::GetVulkanRenderer()->GetInstance(), WindowHandle, nullptr, &wndSurface));
				break;
			}
			default:
				break;
		}

		SetWidgetVisibility(Visibility::Hidden);
		glfwSetWindowSizeLimits(WindowHandle, GetMinSize().Width == 0 ? -1 : GetMinSize().Width, GetMinSize().Height == 0 ? -1 : GetMinSize().Height, GetMaxSize().Width == 0 ? -1 : GetMaxSize().Width, GetMaxSize().Height == 0 ? -1 : GetMaxSize().Height);
		glfwSetWindowUserPointer(WindowHandle, this);

		InitCallbacks();

		Initialized();
		Thread::UnlockThread();

		Application::CurrentApplication->WindowCollection.push_back(this);

		UpdateWindow();
	}

	GLFWwindow* Window::InitWindow()
	{
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CastTo<OpenGL::GLRenderer*>(Application::CurrentApplication->CurrentRenderer)->MajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CastTo<OpenGL::GLRenderer*>(Application::CurrentApplication->CurrentRenderer)->MinorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GetResizable());
		glfwWindowHint(GLFW_DECORATED, GetUseNativeWindowBorder());
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, GetWindowState() == WindowState::Maximized);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);

		switch (Application::CurrentApplication->GetRendererType())
		{
		case Renderer::RendererType::OpenGL:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			break;
		case Renderer::RendererType::Vulkan:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		default:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		}

		GLFWwindow* window = glfwCreateWindow(GetSize().Width, GetSize().Height, GetTitle().c_str(), nullptr, nullptr);

		return window;
	}

	void Window::InitCallbacks()
	{
		Rendered += EventHandler::Bind(&Window::OnWindowRender, this);

		glfwSetWindowCloseCallback(WindowHandle, &Window::CloseCallback);
		glfwSetWindowSizeCallback(WindowHandle, &Window::ResizeCallback);
	}

	void Window::ResizeCallback(GLFWwindow* window, int width, int height)
	{
		CastTo<Window*>(glfwGetWindowUserPointer(window))->SetSize(PSize(width, height));
		CastTo<Window*>(glfwGetWindowUserPointer(window))->OnResize(PSize(width, height));
	}

	void Window::CloseCallback(GLFWwindow* window)
	{
		CastTo<Window*>(glfwGetWindowUserPointer(window))->Close();
	}
}