#pragma once
#include "Core/Core.h"
#include "Core/CoreException.h"
#include "Maths/Size.h"
#include "Core/Events/Event.h"
#include "Core/Debug/Log.h"
#include "Threading/Thread.h"
#include "Core/Rendering/Vulkan/VKRenderer.h"

using namespace Pictura::Maths;
using namespace Pictura::Threading;

namespace Pictura::Widgets
{
	class PICTURA_API Window
	{
	public:
		Window();
		virtual ~Window();

	public:
		Event<void> Shown;
		virtual void OnShown() {}
		void Show();

		Event<void> Closed;
		virtual void OnClosed() {}
		void Close();

		Event<void> Hidden;
		virtual void OnHid() {}
		void Hide();

		Event<void> GotFocus;
		virtual void OnGotFocus() {}
		void Focus();

		Event<void> Updated;
		virtual void OnUpdate() {}
		void Update();

		Event<void> Reset;
		virtual void OnReset() {}
		void ResetWindow(bool finalPhase = false);

	public:
		PSize Size;
		PString Title;
		
	private:
		void DisplayWindow();

		void InitWindow();
		void RemoveWindow();
		void RenderWindow();

		void BindSurface();
		void InitSurface();

		void DestroySurface();


	private:
		PUniquePtr<Thread> windowThread = nullptr;
		bool isOnScreen = false;
		bool isClosing = false;

		//Vulkan specific objects
		VkSurfaceKHR vkSurface = nullptr;
		VkSurfaceFormatKHR vkSurfaceFormat = {};
		VkSurfaceCapabilitiesKHR vkSurfaceCapabilities = {};

#if PLATFORM_WINDOWS == 1
		PString	  win32ClassName;
		HINSTANCE win32Instance = nullptr;
		HWND	  win32Window = nullptr;
		HDC win32hdc = nullptr;
#endif
	};
}