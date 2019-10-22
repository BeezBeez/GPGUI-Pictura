#pragma once
#include "Widgets/Widget.h"
#include "Widgets/WidgetCollection.h"

namespace Pictura::Widgets
{
	class PICTURA_API Window : public Widget
	{
	public:
		enum class WindowState
		{
			Normal = 0,
			Minimized = 1,
			Maximized = 2
		};

	properties:
		NOTIFY_PROPERTY(bool, Resizable, OnResizableChanged, true)
		NOTIFY_PROPERTY(bool, UseNativeWindowBorder, OnUNWBChanged, true)
		NOTIFY_PROPERTY(bool, AlwaysOnTop, OnAlwaysOnTopChanged, false)

		NOTIFY_PROPERTY(PSize, MinSize, OnMinSizeChanged, PSize(200, 200))
		NOTIFY_PROPERTY(PSize, MaxSize, OnMaxSizeChanged, PSize(0, 0))
		NOTIFY_PROPERTY(PString, Title, OnTitleChanged, "Untitled window")
		NOTIFY_PROPERTY(WindowState, WindowState, OnWindowStateChanged, WindowState::Normal)
		NOTIFY_PROPERTY(bool, Focused, OnFocusChanged, false)

		READONLY_PROPERTY(float, FPS, 1.f)

		PROPERTY(float, PixelRatio, 1.f)
		PROPERTY(NVGcontext*, Brush, nullptr)

	public:
		Window();
		virtual ~Window();	

	public:
		Event<void> WindowInitialized;
		Event<void> Shown;
		Event<void> Closed;
		Event<PSize> Resized;
		Event<bool> Focused;

		void Show();
		void Close();
		void Focus();
		void RequestAttention();

		GLFWwindow* WindowHandle = nullptr;
		Graphics::Context* WindowContext;
		WidgetCollection Children;

	private:
		GLFWwindow* InitWindow();

		Graphics::Renderer* renderer = nullptr;

		VkSurfaceKHR wndSurface = nullptr;
		PUniquePtr<Thread> wndThread = nullptr;

		double lastTime;
		int nbFrames = 0;

		void ProcessEvents();
		void UpdateWindow();
		void InitThread();
		void InitCallbacks();

	private:
		static void CloseCallback(GLFWwindow* window);
		static void ResizeCallback(GLFWwindow* window, int width, int height);
		static void FocusCallback(GLFWwindow* window, int focused);

	protected:
		virtual void OnWindowInitialized()
		{
			WindowInitialized();
		}

		virtual void OnShow() { Shown(); }
		virtual void OnClose() { Closed(); }
		virtual void OnResize(PSize NewSize)
		{ 
			int fbW = 0;
			int fbH = 0;
			glfwGetFramebufferSize(WindowHandle, &fbW, &fbH);
			SetPixelRatio((float)fbW / (float)fbH);
			Resized(NewSize);
		}

		virtual void OnFocusChanged(bool PreviousValue, bool NewValue) { Focused(NewValue); }

		virtual void OnResizableChanged(bool PreviousValue, bool NewValue) { glfwSetWindowAttrib(WindowHandle, GLFW_RESIZABLE, NewValue); }
		virtual void OnUNWBChanged(bool PreviousValue, bool NewValue) { glfwSetWindowAttrib(WindowHandle, GLFW_DECORATED, NewValue); }
		virtual void OnAlwaysOnTopChanged(bool PreviousValue, bool NewValue) { glfwSetWindowAttrib(WindowHandle, GLFW_FLOATING, NewValue); }
		virtual void OnMinSizeChanged(PSize PreviousValue, PSize NewValue) { glfwSetWindowSizeLimits(WindowHandle, NewValue.Width == 0.f ? -1 : NewValue.Width, NewValue.Height == 0.f ? -1 : NewValue.Height, GetMaxSize().Width == 0.f ? -1 : GetMaxSize().Width, GetMaxSize().Height == 0.f ? -1 : GetMaxSize().Height); }
		virtual void OnMaxSizeChanged(PSize PreviousValue, PSize NewValue) { glfwSetWindowSizeLimits(WindowHandle, GetMinSize().Width == 0.f ? -1 : GetMinSize().Width, GetMinSize().Height == 0 ? -1 : GetMinSize().Width, NewValue.Width == 0 ? -1 : NewValue.Width, NewValue.Height == 0 ? -1 : NewValue.Height); }
		void OnSizeChanged(PSize PreviousValue, PSize NewValue) override
		{
			int fbW = 0;
			int fbH = 0;
			glfwSetWindowSize(WindowHandle, (float)NewValue.Width, (float)NewValue.Height);
			glfwGetFramebufferSize(WindowHandle, &fbW, &fbH);
			SetPixelRatio((float)fbW / (float)fbH);
			Resized(NewValue); 
		}

		virtual void OnTitleChanged(PString PreviousValue, PString NewValue) { glfwSetWindowTitle(WindowHandle, NewValue.c_str()); }

		virtual void OnWindowRender()
		{
			Children.Update();
		}

		void DrawDebugLimits(Widget* widget)
		{

		}

		virtual void OnWindowStateChanged(WindowState PreviousValue, WindowState NewValue)
		{
			if (WindowHandle)
			{
				switch (NewValue)
				{
					case WindowState::Normal:
					{
						glfwRestoreWindow(WindowHandle);
						break;
					}
					case WindowState::Minimized:
					{
						glfwIconifyWindow(WindowHandle);
						break;
					}
					case WindowState::Maximized:
					{
						glfwMaximizeWindow(WindowHandle);
						break;
					}
					default:
						break;
				}
			}
		}

		void OnVisibilityChanged(Visibility PreviousValue, Visibility NewValue) override
		{
			Widget::OnVisibilityChanged(PreviousValue, NewValue);
			switch (NewValue)
			{
				case Visibility::Visible:
				{
					if (WindowHandle) {
						glfwSetWindowAttrib(WindowHandle, GLFW_FOCUS_ON_SHOW, true);
						glfwShowWindow(WindowHandle);
						glfwSetWindowSizeLimits(WindowHandle, GetMinSize().Width == 0.f ? -1 : GetMinSize().Width, GetMinSize().Height == 0.f ? -1 : GetMinSize().Height, GetMaxSize().Width == 0.f ? -1 : GetMaxSize().Width, GetMaxSize().Height == 0.f ? -1 : GetMaxSize().Height);
						SetWindowState(GetWindowState());
					}
					break;
				}
				case Visibility::Hidden:
				{
					if (WindowHandle) {
						glfwHideWindow(WindowHandle);
					}
					break;
				}
				default:
					break;
			}
		}

		void OnPositionChanged(PPosition PreviousValue, PPosition NewValue) override
		{
			Widget::OnPositionChanged(PreviousValue, NewValue);
			glfwSetWindowPos(WindowHandle, (float)NewValue.X, (float)NewValue.Y);
		}
	};
}