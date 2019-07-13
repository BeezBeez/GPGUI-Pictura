#pragma once
#include "Exception.h"

namespace Pictura
{
	class PICTURA_API WinException : public Exception
	{
	public:
		explicit WinException(PString message) : Exception(message) {}
	};
}
