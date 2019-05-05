#pragma once
#include "PicturaPCH.h"

namespace Pictura
{
	enum class OperatingSystem
	{
		Windows, Linux, Mac
	};

	class PICTURA_API Runtime
	{
	public:
		Runtime();
		~Runtime();

	public:
		static OperatingSystem GetOperatingSystem();
		static PString GetOperatingSystemText();
		static void Debugbreak();
	};
}