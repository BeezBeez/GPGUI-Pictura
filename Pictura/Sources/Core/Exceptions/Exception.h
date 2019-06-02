#pragma once
#include "PicturaPCH.h"
#include "Core/Core.h"
#include "Core/Debug/Log.h"

namespace Pictura
{
	class PICTURA_API Exception : public std::exception
	{
	public:
		explicit Exception(PString message, bool logToConsole = true): msg_(message)
		{
			if (logToConsole)
			{
				Debug::Log::Error("Exception : " + this->GetMessage());
			}
		}

		virtual const PString GetMessage() { return msg_; }

	protected:
		std::string msg_;
	};
}
