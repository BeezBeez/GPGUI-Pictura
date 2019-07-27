#pragma once
#include "PicturaPCH.h"
#include "Core/Core.h"
#include "Core/Debug/Log.h"

namespace Pictura
{
	class PICTURA_API Exception : public std::exception
	{
	public:
		explicit Exception(PString message, PString ExceptionName = "Exception", bool logToConsole = true): msg_(message), ex_name_(ExceptionName)
		{
			if (logToConsole)
			{
				Debug::Log::Error(ex_name_ + " : " + this->GetMessage(), "EXCEPTION");
			}
		}

		virtual const PString GetMessage() { return msg_; }

	protected:
		std::string msg_;
		std::string ex_name_;
	};
}
