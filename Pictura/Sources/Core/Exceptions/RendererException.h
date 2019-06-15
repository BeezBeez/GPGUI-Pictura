#pragma once
#include "Exception.h"

namespace Pictura::Graphics
{
	class PICTURA_API RendererException : public Exception
	{
	public:
		explicit RendererException(PString message) : Exception(message) {}
	};
}
