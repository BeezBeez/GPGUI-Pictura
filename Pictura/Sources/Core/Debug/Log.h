#pragma once
#include "Core/Core.h"
#include "Core/Timers/DateTime.h"
#include "Core/System/Console.h"

namespace Pictura::Debug
{
	class PICTURA_API Log
	{
	public:
		Log();
		~Log();

	public:
		static void Trace  (PString message, PString context   = "PICTURA");
		static void Info   (PString message, PString context   = "PICTURA");
		static void Success(PString message, PString context   = "PICTURA");
		static void Warning(PString message, PString context   = "PICTURA");
		static void Error  (PString message, PString context   = "PICTURA");
		static void BlankLine();
	};
}

