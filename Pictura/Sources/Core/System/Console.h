#pragma once
#include "Core/Core.h"

namespace Pictura
{
	class PICTURA_API Console
	{
	public:
		Console();
		~Console();

		enum class ConsoleColor
		{
			Black = 0, Grey = 7, White = 15,
			Red = 12, DarkRed = 4, Green = 10, DarkGreen = 2,
			Yellow = 14, DarkYellow = 6, Blue = 9, DarkBlue = 1,
			Magenta = 13, DarkMagenta = 5, Cyan = 11, DarkCyan = 3
		};

	public:
		static void WriteLine(PString message,Console::ConsoleColor TextColor = ConsoleColor::Grey);
		static void Pause(PString pauseMessage = "Press [ENTER] to continue program execution...");
		static bool IsANSISupported();
		static PMutex ConsoleMutex;
	};
};