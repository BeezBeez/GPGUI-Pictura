#pragma once

namespace Pictura
{
	class PICTURA_API Application;
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
		static void Assert(bool condition, PString message = "Unknown reason", PString context = "PICTURA");

	public:
		static PVector<PString> Arguments;
		static Application* CurrentApplication;
	};
}