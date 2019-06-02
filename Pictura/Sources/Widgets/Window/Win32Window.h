#pragma once
#include "Window.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Pictura::Widgets::Windows
{
	class Win32Window : public Window
	{
	public:
		Win32Window();
		virtual ~Win32Window();

	};
}