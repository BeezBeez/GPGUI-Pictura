#pragma once
#include "Core/Core.h"
#include "GLFW/glfw3.h"

namespace Pictura::Graphics
{
	class PICTURA_API Context
	{
	public:
		typedef void* ContextPtr;
		virtual void Init(bool Debug = false) = 0;

	public:
		ContextPtr Get()
		{
			return ctx;
		}

		GLFWwindow* GetWindowHandle()
		{
			return wnd;
		}

		void SetWindowHandle(GLFWwindow* wndHandle)
		{
			wnd = wndHandle;
		}

		void SetPtr(ContextPtr ctxPtr)
		{
			ctx = ctxPtr;
		}

	private:
		ContextPtr ctx = nullptr;
		GLFWwindow* wnd = nullptr;
	};
}