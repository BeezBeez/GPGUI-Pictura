#pragma once

#include "PlatformMacro.h"

#if PLATFORM_WINDOWS == 1
#include <Windows.h>
#include <wrl.h>
using namespace Microsoft::WRL;

#define VK_USE_PLATFORM_WIN32_KHR 1
#define SURFACE_EXTENSION_NAME "VK_KHR_win32_surface"

#ifdef _MSC_VER
	#define VISUALSTUDIO_VERSION _MSC_VER
#endif

#define DEBUGBREAK DebugBreak()

#else
	#define DEBUGBREAK __debugbreak()
#endif

#if PLATFORM_LINUX == 1
#define VK_USE_PLATFORM_XCB_KHR 1
#define SURFACE_EXTENSION_NAME "VK_KHR_xcb_surface"
#endif

#if PLATFORM_OSX == 1
#define VK_USE_PLATFORM_MACOS_MVK 1
#define SURFACE_EXTENSION_NAME "VK_MVK_macos_surface"
#endif

#ifdef PICTURA_LIB
	#define PICTURA_API __declspec(dllexport)
#else
	#define PICTURA_API __declspec(dllimport)
#endif

#ifdef VISUALSTUDIO_VERSION
	#define DEBUG_OUTPUT( s )            \
	{                             \
	   std::ostringstream os_;    \
	   os_ << s << '\n';                   \
	   OutputDebugString( os_.str().c_str() );  \
	}
#endif

#include <vulkan/vulkan.h>
#include "PicturaTypes.h"