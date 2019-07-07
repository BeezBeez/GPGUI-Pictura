#pragma once
#include "Core/Core.h"

namespace Pictura
{
	class PICTURA_API Runtime
	{
	public:
		Runtime();
		~Runtime();

		enum class OperatingSystem
		{
			Windows, Linux, Mac
		};

	public:
		static Runtime::OperatingSystem GetOperatingSystem();
		static PString GetOperatingSystemText();
		static void Debugbreak();
		static void Assert(bool condition, const PString& message = "Unknown reason", PString context = "PICTURA");
		static void ForceExitApplication();
	};
}
