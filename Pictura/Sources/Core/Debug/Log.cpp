#include "PicturaPCH.h"
#include "Log.h"

#include "Core/Timers/DateTime.h"
#include "Core/System/Console.h"

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
		Console::WriteLine("[" + Pictura::DateTime::GetCurrentTimeFormat() + " - " + context + "] " + message);
	}

	void Log::Info(PString message, PString context)
	{
		Console::WriteLine("[" + Pictura::DateTime::GetCurrentTimeFormat() + " - " + context + "] " + message, Console::ConsoleColor::Cyan);
	}

	void Log::Success(PString message, PString context)
	{
		Console::WriteLine("[" + Pictura::DateTime::GetCurrentTimeFormat() + " - " + context + "] " + message, Console::ConsoleColor::DarkGreen);
	}

	void Log::Warning(PString message, PString context)
	{
		Console::WriteLine("[" + Pictura::DateTime::GetCurrentTimeFormat() + " - " + context + "] " + message, Console::ConsoleColor::Yellow);
	}

	void Log::Error(PString message, PString context)
	{
		Console::WriteLine("[" + Pictura::DateTime::GetCurrentTimeFormat() + " - " + context + "] " + message, Console::ConsoleColor::Red);
	}

	void Log::BlankLine()
	{
		Console::WriteLine("");
	}

}
