#pragma once
#include "Core/Rendering/Renderer.h"
#include "Core/Exceptions/RendererException.h"

namespace Pictura::Graphics::D3D12
{
	class PICTURA_API D3D12Renderer : public Renderer
	{
		void Init() override
		{
			Debug::Log::Warning("DirectX 12 Renderer wasn't implemented!", "RENDERER");
		}

		void Destroy() override
		{
			
		}
	};
}