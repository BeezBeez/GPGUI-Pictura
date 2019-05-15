#pragma once

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
	};
}