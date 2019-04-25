#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM_MACOS
#elif defined(__unix__) || defined(__unix)
	#define PLATFORM_LINUX
#else
	#error unsupported platform
#endif

#ifdef PICTURA_LIB
	#define PICTURA_API __declspec(dllexport)
#else
	#define PICTURA_API __declspec(dllimport)
#endif

#include "PicturaTypes.h"