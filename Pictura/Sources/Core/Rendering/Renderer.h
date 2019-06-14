#pragma once
#include "Core/Core.h"
#include "Core/Debug/Log.h"

namespace Pictura::Graphics
{
	class Renderer
	{
	public:
		Renderer()
		{
			Debug::Log::Trace("Inside parent renderer", "RENDERER");
		}
	
		virtual ~Renderer();

		virtual void Init();
		virtual void Destroy();
	};
}
