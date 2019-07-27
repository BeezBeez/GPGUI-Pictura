#pragma once
namespace Pictura::Maths
{
	struct PSize
	{
		uint32 Width, Height;
		PSize() : Width(0), Height(0) {}
		PSize(uint32 Width, uint32 Height) : Width(Width), Height(Height) {}
		operator PString() const { return "Width[" + Types::ToString(Width) + "] Height[" + Types::ToString(Height) + "]"; }
		operator PString() { return "Width[" + Types::ToString(Width) + "] Height[" + Types::ToString(Height) + "]"; }
	};
}