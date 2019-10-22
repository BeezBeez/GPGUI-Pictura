#pragma once
namespace Pictura::Maths
{
	struct PSize
	{
		float Width, Height;

		PSize() : Width(0), Height(0) {}
		PSize(float Width, float Height) : Width(Width), Height(Height) {}

		operator PString() const { return "Width[" + Types::ToString(Width) + "] Height[" + Types::ToString(Height) + "]"; }
		operator PString() { return "Width[" + Types::ToString(Width) + "] Height[" + Types::ToString(Height) + "]"; }
	};
}