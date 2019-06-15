#pragma once

#include "Core/Core.h"
#include "Maths/Size.h"
#include "Core/Debug/Log.h"

using namespace Pictura::Maths;

namespace Pictura::Widgets
{
	class PICTURA_API Window
	{
	public:

		Window() {}

		virtual ~Window()
		{
			
		}

	public:
		virtual void Show() {}
		virtual void Close() {}

	public:
		PSize Size;
		PString Title;
	public:
		static PUniquePtr<Window> Create();
	private:
		
	};
}