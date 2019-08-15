#pragma once
#include "Widgets/Widget.h"

using namespace Pictura::Maths;
using namespace Pictura::Threading;

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

	public:
		Window();
		virtual ~Window();
		
		NOTIFY_PROPERTY(bool, Resizable, OnResizableChanged, true)
		NOTIFY_PROPERTY(bool, UseNativeWindowBorder, OnUNWBChanged, true)
		NOTIFY_PROPERTY(bool, AlwaysOnTop, OnAlwaysOnTopChanged, false)
		NOTIFY_PROPERTY(PSize, Size, OnSizeChanged, PSize(640,480))
		NOTIFY_PROPERTY(PSize, MinSize, OnMinSizeChanged, PSize(200,200))
		NOTIFY_PROPERTY(PSize, MaxSize, OnMaxSizeChanged, PSize(0, 0))
		NOTIFY_PROPERTY(PString, Title, OnTitleChanged, "Untitled window")
		NOTIFY_PROPERTY(WindowState, WindowState, OnWindowStateChanged, WindowState::Normal)

	public:
		Event<void> Initialized;
		Event<void> Shown;
		Event<void> Closed;
		Event<PSize> Resized;

		void Show();
		void Close();
		void AddWidget(Widget* widget);
		void RemoveWidget(Widget* widget);

		GLFWwindow* WindowHandle = nullptr;

	private:
		GLFWwindow* InitWindow();

		Graphics::Renderer* renderer = nullptr;
		PVector<Widget*> Children = {};

		VkSurfaceKHR wndSurface = nullptr;
		PUniquePtr<Thread> wndThread = nullptr;

		void ProcessEvents();
		void UpdateWindow();
		void InitThread();
		void InitCallbacks();

	private:
		static void CloseCallback(GLFWwindow* window);
		static void ResizeCallback(GLFWwindow* window, int width, int height);

	protected:
		virtual void OnShow() { Shown(); }
		virtual void OnClose() { Closed(); }
		virtual void OnResize(PSize NewSize) { Resized(NewSize); }

		virtual void OnResizableChanged(bool PreviousValue, bool NewValue) { glfwSetWindowAttrib(WindowHandle, GLFW_RESIZABLE, NewValue); }
		virtual void OnUNWBChanged(bool PreviousValue, bool NewValue) { glfwSetWindowAttrib(WindowHandle, GLFW_DECORATED, NewValue); }
		virtual void OnAlwaysOnTopChanged(bool PreviousValue, bool NewValue) { glfwSetWindowAttrib(WindowHandle, GLFW_FLOATING, NewValue); }
		virtual void OnMinSizeChanged(PSize PreviousValue, PSize NewValue) { glfwSetWindowSizeLimits(WindowHandle, NewValue.Width == 0 ? -1 : NewValue.Width, NewValue.Height == 0 ? -1 : NewValue.Height, GetMaxSize().Width == 0 ? -1 : GetMaxSize().Width, GetMaxSize().Height == 0 ? -1 : GetMaxSize().Height); }
		virtual void OnMaxSizeChanged(PSize PreviousValue, PSize NewValue) { glfwSetWindowSizeLimits(WindowHandle, GetMinSize().Width == 0 ? -1 : GetMinSize().Width, GetMinSize().Height == 0 ? -1 : GetMinSize().Width, NewValue.Width == 0 ? -1 : NewValue.Width, NewValue.Height == 0 ? -1 : NewValue.Height); }
		virtual void OnSizeChanged(PSize PreviousValue, PSize NewValue) { glfwSetWindowSize(WindowHandle, NewValue.Width, NewValue.Height); Resized(NewValue); }
		virtual void OnTitleChanged(PString PreviousValue, PString NewValue) { glfwSetWindowTitle(WindowHandle, NewValue.c_str()); }

		virtual void OnWindowRender()
		{
			for (auto widget : Children)
			{
				widget->Update();
				widget->Render();
			}
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
						glfwSetWindowSizeLimits(WindowHandle, GetMinSize().Width == 0 ? -1 : GetMinSize().Width, GetMinSize().Height == 0 ? -1 : GetMinSize().Height, GetMaxSize().Width == 0 ? -1 : GetMaxSize().Width, GetMaxSize().Height == 0 ? -1 : GetMaxSize().Height);
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
			glfwSetWindowPos(WindowHandle, NewValue.X, NewValue.Y);
		}
	};
}