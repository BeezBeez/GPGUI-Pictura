#include "PicturaPCH.h"
#include "Console.h"

namespace Pictura
{

	Console::Console()
	{

	}

	Console::~Console()
	{

	}

	void Console::WriteLine(PString message, Console::ConsoleColor TextColor)
	{
		PString code;

#ifndef PLATFORM_WINDOWS //Unix system code (Use ANSI escape sequence)
		switch (TextColor)
		{
		case Pictura::Console::ConsoleColor::Black:
			code = "\033[0;30;40m";
			break;
		case Pictura::Console::ConsoleColor::Grey:
			code = "\033[0;37;40m";
			break;
		case Pictura::Console::ConsoleColor::White:
			code = "\033[1;37;40m";
			break;
		case Pictura::Console::ConsoleColor::Red:
			code = "\033[1;31;40m";
			break;
		case Pictura::Console::ConsoleColor::DarkRed:
			code = "\033[0;31;40m";
			break;
		case Pictura::Console::ConsoleColor::Green:
			code = "\033[1;32;40m";
			break;
		case Pictura::Console::ConsoleColor::DarkGreen:
			code = "\033[0;32;40m";
			break;
		case Pictura::Console::ConsoleColor::Yellow:
			code = "\033[1;33;40m";
			break;
		case Pictura::Console::ConsoleColor::DarkYellow:
			code = "\033[0;33;40m";
			break;
		case Pictura::Console::ConsoleColor::Blue:
			code = "\033[1;34;40m";
			break;
		case Pictura::Console::ConsoleColor::DarkBlue:
			code = "\033[0;34;40m";
			break;
		case Pictura::Console::ConsoleColor::Magenta:
			code = "\033[1;35;40m";
			break;
		case Pictura::Console::ConsoleColor::DarkMagenta:
			code = "\033[0;35;40m";
			break;
		case Pictura::Console::ConsoleColor::Cyan:
			code = "\033[1;36;40m";
			break;
		case Pictura::Console::ConsoleColor::DarkCyan:
			code = "\033[0;36;40m";
			break;
		default:
			code = "\033[1;37;40m";
			break;
		}
		std::cout << code + message + "\033[0m" << std::endl;
#else                    //Windows NT system code (Use Console API)
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int color;

		color = to_underlying(TextColor);

		FlushConsoleInputBuffer(hConsole);
		SetConsoleTextAttribute(hConsole, color);

		std::cout << message << std::endl;

		SetConsoleTextAttribute(hConsole, 7);
#endif
	}

	bool Console::IsANSISupported()
	{	
		return !(Runtime::GetOperatingSystem() == Runtime::OperatingSystem::Windows);
	}
}

