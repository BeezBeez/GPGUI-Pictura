#pragma once
#include "Window.h"

using namespace Pictura::Widgets;

namespace Pictura::Widgets::Windows
{
	class PICTURA_API Win32Window : public Window
	{
	public:
		Win32Window();
		virtual ~Win32Window();

	};
}