#pragma once
namespace Pictura::Maths
{
	struct Size
	{
		int Width, Height;
		Size() : Width(0), Height(0) {}
		Size(int Width, int Height) : Width(Width), Height(Height) {}
	};
}