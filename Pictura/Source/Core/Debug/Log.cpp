#include "PicturaPCH.h"
#include "Log.h"

namespace Pictura::Debug
{

	Log::Log()
	{
	}

	Log::~Log()
	{
	}

	void Log::Trace(PString message, PString context)
	{
		Console::WriteLine("[DATE - " + context + "] " + message);
	}

	void Log::Success(PString message, PString context)
	{
		Console::WriteLine("[DATE - " + context + "] " + message, Console::ConsoleColor::Green);
	}

	void Log::Warning(PString message, PString context)
	{
		Console::WriteLine("[DATE - " + context + "] " + message, Console::ConsoleColor::Yellow);
	}

	void Log::Error(PString message, PString context)
	{
		Console::WriteLine("[DATE - " + context + "] " + message, Console::ConsoleColor::Red);
	}

}
