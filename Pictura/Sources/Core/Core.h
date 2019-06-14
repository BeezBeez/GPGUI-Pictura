#pragma once

#include "PlatformMacro.h"

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