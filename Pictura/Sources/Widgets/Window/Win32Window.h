#pragma once
#include "Window.h"

using namespace Pictura::Widgets;

namespace Pictura::Widgets::Windows
{
	class Win32Window : public Window
	{
	public:
		Win32Window();
		virtual ~Win32Window();

	public:
		void Show() override;
		void Close() override;
	};
}