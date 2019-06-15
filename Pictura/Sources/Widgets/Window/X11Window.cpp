#include "PicturaPCH.h"
#include "X11Window.h"

#if PLATFORM_LINUX == 1
namespace Pictura::Widgets
{
	PUniquePtr<Window> Window::Create()
	{
		Debug::Log::Trace("Creating a Win32 Window");
		return PUniquePtr<Window>(Types::MakeUnique<X11::X11Window>());
	}
}
#endif

namespace Pictura::Widgets::X11
{
	X11Window::X11Window()
	{
		
	}

	X11Window::~X11Window()
	{
		
	}
}