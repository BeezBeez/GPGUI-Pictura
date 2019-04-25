#pragma once
namespace Pictura
{
	struct DateTime
	{
	public:
		DateTime();
		~DateTime();
		
		DateTime GetSystemTime(PString format = "%c");
	public:
		int Second;
		int Minute;
		int Hour;
		int Day;
		int Month;
		int Year;
	};
}

