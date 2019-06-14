#pragma once
#include "Core/Core.h"

namespace Pictura
{
	struct DateTime
	{
	public:
		DateTime();
		~DateTime();

		static DateTime GetCurrentTime();
		static PString GetCurrentTimeFormat(PString format = "%T");
	public:
		int Second;
		int Minute;
		int Hour;
		int Day;
		PString FullDay;
		int Month;
		PString FullMonth;
		int Year;
	};
}

