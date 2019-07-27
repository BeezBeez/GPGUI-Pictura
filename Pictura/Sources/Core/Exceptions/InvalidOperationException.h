#pragma once
#include "Exception.h"

namespace Pictura
{
	class PICTURA_API InvalidOperationException : public Exception
	{
	public:
		explicit InvalidOperationException(PString message) : Exception(message, "InvalidOperationException") {}
	};
}
