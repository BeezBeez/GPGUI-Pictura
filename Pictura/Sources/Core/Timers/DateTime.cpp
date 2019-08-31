#include "PicturaPCH.h"
#include "DateTime.h"

namespace Pictura
{
	DateTime::DateTime()
	{
		Second = 0;
		Minute = 0;
		Hour   = 0;
		Day    = 0;
		Month  = 0;
		Year   = 0;
	}


	DateTime::~DateTime()
	{
		
	}

	DateTime DateTime::GetCurrentTime()
	{
		DateTime r;
		r.Second = std::atoi(GetCurrentTimeFormat("%S").c_str());
		r.Minute = std::atoi(GetCurrentTimeFormat("%M").c_str());
		r.Hour = std::atoi(GetCurrentTimeFormat("%H").c_str());

		r.Day = std::atoi(GetCurrentTimeFormat("%d").c_str());
		r.FullDay = GetCurrentTimeFormat("%A");
		r.Month = std::atoi(GetCurrentTimeFormat("%m").c_str());
		r.FullMonth = GetCurrentTimeFormat("%B");
		r.Year = std::atoi(GetCurrentTimeFormat("%Y").c_str());

		return r;
	}

	PString DateTime::GetCurrentTimeFormat(PString format)
	{
		auto currentTime = std::chrono::system_clock::now();
		std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
		
		std::time_t t = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &t);

		try
		{
			std::stringstream buffer;
			buffer << std::put_time(&tm, format.c_str());

			return buffer.str();
		}
		catch (const std::exception&)
		{
			return "INVALID TIME";
		}
	}
}
