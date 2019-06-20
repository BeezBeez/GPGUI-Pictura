#pragma once
#include "Core/Core.h"
#include "CommandPool.h"

namespace Pictura::Graphics
{
	class PICTURA_API CommandBuffer
	{
	public:
		virtual ~CommandBuffer() {}

	public:
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Send() = 0;
		virtual void SendAndWait() = 0;

	protected:
		CommandPool* m_CommandPool = nullptr;
	};
}
