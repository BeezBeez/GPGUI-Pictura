#pragma once
namespace Pictura::Maths
{
	struct PSize
	{
		int Width, Height;
		PSize() : Width(0), Height(0) {}
		PSize(int Width, int Height) : Width(Width), Height(Height) {}
	};
}