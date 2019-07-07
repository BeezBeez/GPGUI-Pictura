#pragma once
#include "PicturaPCH.h"
#include "Core/Core.h"

namespace Pictura::Maths
{
	class Convert
	{
	public:
		static PString ToHexadecimal(uint32 Num, bool ShowFirstZero = true)
		{
			std::stringstream ss;
			ss << std::hex << Num;

			return ShowFirstZero ? "0x" + ss.str() : ss.str();
		}

		static PString ToHexadecimal(uint64 Num, bool ShowFirstZero = true)
		{
			std::stringstream ss;
			ss << std::hex << Num;

			return ShowFirstZero ? "0x" + ss.str() : ss.str();
		}
	private:

	};
}