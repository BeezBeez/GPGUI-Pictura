#pragma once
namespace Pictura::Maths
{
	struct PSize
	{
		uint32_t Width, Height;
		PSize() : Width(0), Height(0) {}
		PSize(uint32_t Width, uint32_t Height) : Width(Width), Height(Height) {}
	};
}