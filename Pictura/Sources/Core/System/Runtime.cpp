#include "PicturaPCH.h"
#include "Runtime.h"
#include <utility>
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
		#if PLATFORM_WINDOWS == 1	
			return Runtime::OperatingSystem::Windows;
		#endif

		#if PLATFORM_LINUX == 1	
			return Runtime::OperatingSystem::Linux;
		#endif

		#if PLATFORM_OSX == 1	
			return Runtime::OperatingSystem::Mac;
		#endif
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

	void Runtime::Assert(bool condition, const PString& message, PString context)
	{
		if (condition)
		{
			Debug::Log::Error("Assertion failed : " + message, std::move(context));
			Debugbreak();
		}
	}

	void Runtime::ForceExitApplication()
	{
		std::exit(9999);
	}

}
