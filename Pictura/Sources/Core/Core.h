#pragma once

#include "PlatformMacro.h"

#define STB_TRUETYPE_IMPLEMENTATION

#ifdef _DEBUG
#define DEBUG_SECTION(instructions) { ##instructions }
#else
#define DEBUG_SECTION(instructions)
#endif

#if PLATFORM_WINDOWS == 1
#include <Windows.h>
#ifdef __cplusplus
	#include <wrl.h>
	using namespace Microsoft::WRL;
#endif

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

#ifdef BUILD_DYNAMIC_LIBRARY
	#ifdef PICTURA_DLL
		#define PICTURA_API __declspec(dllexport)
	#else
		#define PICTURA_API __declspec(dllimport)
	#endif
#else
	#define PICTURA_API
#endif
#ifdef VISUALSTUDIO_VERSION
	#define DEBUG_OUTPUT( s )            \
	{                             \
	   std::ostringstream os_;    \
	   os_ << s << '\n';                   \
	   OutputDebugString( os_.str().c_str() );  \
	}
#endif

#include "glad/gl.h"
#include "glad/vulkan.h"
#include "PicturaTypes.h"
#include "System/Property.h"