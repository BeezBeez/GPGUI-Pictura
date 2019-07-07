#pragma once
#include "Exception.h"

namespace Pictura
{
	class PICTURA_API ThreadException : public Exception
	{
	public:
		explicit ThreadException(PString message) : Exception(message) {}
	};
}
