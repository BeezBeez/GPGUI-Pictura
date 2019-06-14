#pragma once

#include "Core/Core.h"
#include "Maths/Size.h"

using namespace Pictura::Maths;

namespace Pictura::Widgets
{
	class PICTURA_API Window
	{
	public:
		Window() {}
		virtual ~Window() {}

	public:
		void Show();
		void Close();

	public:
		PSize Size;
	};
}