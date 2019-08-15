#pragma once
#include "Exception.h"

namespace Pictura
{
	class PICTURA_API MemoryException : public Exception
	{
	public:
		explicit MemoryException(PString message) : Exception(message, "MemoryException") {}
	};
}
