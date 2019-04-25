#include "Core.h"

namespace Pictura
{
	class PICTURA_API Console
	{
	public:
		Console();
		~Console();

		enum class ConsoleColor
		{
			Black, Grey, White,
			Red, DarkRed, Green, DarkGreen,
			Yellow, DarkYellow, Blue, DarkBlue,
			Magenta, DarkMagenta, Cyan, DarkCyan
		};

	public:
		static void WriteLine(PString message,Console::ConsoleColor TextColor = ConsoleColor::Grey);

	};
};