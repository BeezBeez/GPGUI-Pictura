#pragma once
#include "Core/Core.h"

namespace Pictura::Graphics
{
	class PICTURA_API CommandPool
	{
	public:
		virtual ~CommandPool() {}

		const std::thread::id& GetThreadId() const { return ThreadId; }

	protected:
		std::thread::id ThreadId;
	};
}
