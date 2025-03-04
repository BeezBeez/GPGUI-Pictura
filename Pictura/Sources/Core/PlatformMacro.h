#pragma once

#define PLATFORM_WINDOWS 0
#define PLATFORM_LINUX 0
#define PLATFORM_OSX 0
#define _GLFW_VULKAN_STATIC

#if defined(_WIN32) || defined(_MINGW32) || defined(_WIN64)
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