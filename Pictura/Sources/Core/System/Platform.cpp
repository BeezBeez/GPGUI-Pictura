#include "Platform.h"
namespace Pictura
{
	Runtime::Runtime()
	{

	}

	Runtime::~Runtime()
	{

	}

    OperatingSystem Runtime::GetOperatingSystem()
	{
		if (PLATFORM_WINDOWS)
		{
			return OperatingSystem::Windows;
		}

		if (PLATFORM_LINUX)
		{
			return OperatingSystem::Linux;
		}

		if (PLATFORM_OSX)
		{
			return OperatingSystem::Mac;
		}
	}

	PString Runtime::GetOperatingSystemText()
	{
		switch (GetOperatingSystem())
		{
		case OperatingSystem::Windows:
			return "Windows";
			break;
		case OperatingSystem::Linux:
			return "Linux";
			break;
		case OperatingSystem::Mac:
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
}
