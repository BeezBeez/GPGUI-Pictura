#pragma once
#include "Exception.h"

namespace Pictura::Types
{
	class PICTURA_API TypeException : public Exception
	{
	public:
		explicit TypeException(PString message) : Exception(message, "TypeException") {}
	};
}
