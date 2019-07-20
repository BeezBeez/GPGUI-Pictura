﻿#include "PicturaPCH.h"
#include "Window.h"
#include "Core/System/Application.h"
#include "Core/System/Runtime.h"

#if PLATFORM_WINDOWS == 1
namespace Pictura::Widgets
{
	LRESULT CALLBACK WindowsEventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto window = ReinterpretCastTo<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (uMsg)
		{
		case WM_CLOSE:
			window->Close();
			break;
		case WM_SIZE:

			break;
		default: 
			break;
		}
		
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void Window::InitWindow()
	{
		if (Size.Width <= 0) {
			Size.Width = 800;
		}

		if (Size.Height <= 0)
		{
			Size.Height = 600;
		}

		WNDCLASSEX winClass{};
		win32Instance = GetModuleHandle(nullptr);
		win32ClassName = Types::ToString(uint64(this));
		const char* wcn = win32ClassName.c_str();
		
		winClass.cbSize = sizeof(WNDCLASSEX);
		winClass.style = CS_HREDRAW | CS_VREDRAW;
		winClass.lpfnWndProc = WindowsEventHandler;
		winClass.cbClsExtra = 0;
		winClass.cbWndExtra = 0;
		winClass.hInstance = win32Instance;
		winClass.hIcon = LoadIcon(win32Instance, IDI_APPLICATION);
		winClass.hCursor = LoadCursor(win32Instance, IDC_ARROW);
		winClass.hbrBackground = HBRUSH(GetStockObject(WHITE_BRUSH));
		winClass.lpszMenuName = nullptr;
		winClass.lpszClassName = wcn;
		winClass.hIconSm = LoadIcon(win32Instance, IDI_APPLICATION);

		Debug::Log::Trace("Creating Win32 Window [TITLE : " + Title + "]", "WINDOW");

		if (!RegisterClassEx(&winClass))
		{
			fflush(stdout);
			throw InvalidOperationException("Failed to register the Window class ! ERROR-" + GetLastError());
			Runtime::ForceExitApplication();
		}

		DWORD exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD style = WS_OVERLAPPEDWINDOW;

		RECT wr = { 0, 0, LONG(Size.Width), LONG(Size.Height) };
		AdjustWindowRectEx(&wr, style, FALSE, exStyle);
		win32Window = CreateWindowEx(0, wcn, Title.c_str(), style, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, win32Instance, NULL);

		if (!win32Window)
		{
			fflush(stdout);
			throw InvalidOperationException("Failed to create a Win32 Window object ! ERROR-" + Types::ToString(GetLastError()));
			Runtime::ForceExitApplication();
		}

		SetWindowLongPtr(win32Window, GWLP_USERDATA, LONG_PTR(this));

		win32hdc = GetDC(win32Window);
		if (win32hdc == nullptr)
		{
			DestroyWindow(win32Window);
			throw WinException("Failed to get Window's device context !");
		}

		PIXELFORMATDESCRIPTOR pfd = { };
		pfd.nSize = sizeof(pfd);
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32; 
		pfd.cDepthBits = 32;        
		pfd.iLayerType = PFD_MAIN_PLANE;
		int format = ChoosePixelFormat(win32hdc, &pfd);

		if (format == 0 || SetPixelFormat(win32hdc, format, &pfd) == FALSE) {
			ReleaseDC(win32Window, win32hdc);
			DestroyWindow(win32Window);
			throw RendererException("Failed to set a compatible pixel format !");
		}
	}

	void Window::RemoveWindow()
	{
		DestroyWindow(win32Window);
		UnregisterClass(win32ClassName.c_str(), win32Instance);
		windowThread.reset();
		isOnScreen = false;
	}

	void Window::BindSurface()
	{
		switch (Application::CurrentApplication->GetRendererType())
		{
			case Renderer::RendererType::Vulkan:
			{
				auto VKRendererRef = ReinterpretCastTo<Vulkan::VKRenderer*>(Application::CurrentApplication->CurrentRenderer);

				VkWin32SurfaceCreateInfoKHR createInfo {};
				createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
				createInfo.hinstance = win32Instance;
				createInfo.hwnd = win32Window;
				vkCreateWin32SurfaceKHR(*VKRendererRef->GetInstance(), &createInfo, nullptr, &vkSurface);
				break;
			}
			default:
				break;
		}
	}

	void Window::Show()
	{
		if (win32Window == nullptr)
		{
			windowThread = Types::MakeUnique<Thread>(&Window::DisplayWindow, this);
			Application::CurrentApplication->WindowCollection.push_back(this);
		}
		else
		{
			if (!IsWindowVisible(win32Window))
			{
				ShowWindow(win32Window, SW_SHOW);
				UpdateWindow(win32Window);
				Focus();
				Shown();
			}
			else {
				Debug::Log::Error("WOOOOOOOOOW !!!");
			}
		}
	}

	void Window::Hide()
	{
		if (isOnScreen)
		{
			ShowWindow(win32Window, SW_HIDE);
		}
	}

	void Window::RenderWindow()
	{
		MSG msg;
		if (GetMessage(&msg, win32Window, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window::Focus()
	{
		SetForegroundWindow(win32Window);
		SetFocus(win32Window);
		GotFocus();
	}

	void Window::DisplayWindow()
	{
		InitWindow();
		ShowWindow(win32Window, SW_SHOW);
		UpdateWindow(win32Window);
		Focus();
		Shown();
		InitSurface();
		isOnScreen = true;
		Update();
	}
}
#endif