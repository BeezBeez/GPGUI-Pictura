#include "PicturaPCH.h"
#include "Win32Window.h"

#if PLATFORM_WINDOWS == 1
namespace Pictura::Widgets
{
	PUniquePtr<Window> Window::Create()
	{
		Debug::Log::Trace("Creating a Win32 Window");
		return PUniquePtr<Window>(Types::MakeUnique<Windows::Win32Window>());
	}

}
#endif

namespace Pictura::Widgets::Windows
{
	Win32Window::Win32Window()
	{
		
	}

	Win32Window::~Win32Window()
	{
		
	}

	void Win32Window::Show()
	{
		Debug::Log::Trace("Showing window with title \"" + Title + "\"");
	}

	void Win32Window::Close()
	{
		
	}


}