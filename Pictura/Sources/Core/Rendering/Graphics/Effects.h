#pragma once
#include "Core/Core.h"

namespace Pictura::Graphics::Effects
{
	struct DropShadowEffect
	{
		float OffsetX, OffsetY, BlurSize;

		DropShadowEffect(float X, float Y, float Size)
		{
			OffsetX = X;
			OffsetY = Y;
			BlurSize = Size;
		}
	};
}