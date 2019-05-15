#pragma once
#include "Exception.h"

namespace Pictura::Filesystem
{
	class PICTURA_API IOException : public Exception
	{
	public:
		explicit IOException(PString message) : Exception(message) {}
	};
}
