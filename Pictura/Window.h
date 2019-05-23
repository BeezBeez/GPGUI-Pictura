#pragma once
#include "Maths\Size.h"

using namespace Pictura::Maths;

namespace Pictura::Widgets
{
	class PICTURA_API Window
	{
	public:
		Window() : WindowSize(Size(640, 480)) {}
		~Window();
	public:
		void Show();
		void Close();

	public:
		Size WindowSize;
	};
}

