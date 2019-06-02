#include "PicturaPCH.h"
#include "Runtime.h"
#include "Core/Debug/Log.h"

namespace Pictura
{
	Runtime::Runtime()
	{

	}

	Runtime::~Runtime()
	{

	}

    Runtime::OperatingSystem Runtime::GetOperatingSystem()
	{
		if (PLATFORM_WINDOWS)
		{
			return Runtime::OperatingSystem::Windows;
		}

		if (PLATFORM_LINUX)
		{
			return Runtime::OperatingSystem::Linux;
		}

		if (PLATFORM_OSX)
		{
			return Runtime::OperatingSystem::Mac;
		}
	}

	PString Runtime::GetOperatingSystemText()
	{
		switch (GetOperatingSystem())
		{
		case Runtime::OperatingSystem::Windows:
			return "Windows";
			break;
		case Runtime::OperatingSystem::Linux:
			return "Linux";
			break;
		case Runtime::OperatingSystem::Mac:
			return "Mac";
			break;
		default:
			return "Unknown operating system";
			break;
		}
	}

	void Runtime::Debugbreak()
	{
		DEBUGBREAK;
	}

	void Runtime::Assert(bool condition, PString message, PString context)
	{
		if (!(condition))
		{
			Debug::Log::Error("Assertion failed : " + message, context);
			Debugbreak();
		}
	}
}
