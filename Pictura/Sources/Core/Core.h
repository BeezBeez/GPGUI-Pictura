#pragma once

#define PLATFORM_WINDOWS 0
#define PLATFORM_LINUX 0
#define PLATFORM_OSX 0

#if defined(_WIN32) || defined(_MINGW32)
#undef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS 1
#elif __APPLE__
#undef PLATFORM_OSX
#define PLATFORM_OSX 1
#elif __linux__
#undef PLATFORM_LINUX
#define PLATFORM_LINUX 1
#else
#error "Unknown runtime platform"
#endif

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
	#ifdef _MSC_VER
		#define VISUALSTUDIO_VERSION _MSC_VER
	#endif
	#define DEBUGBREAK DebugBreak()
#else
	#define DEBUGBREAK __debugbreak()
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

#include "PicturaTypes.h"