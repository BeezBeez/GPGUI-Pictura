#pragma once
#include "Core/Core.h"
#include "NanoVG/nanovg.h"

namespace Pictura::Graphics
{
	struct PICTURA_API Color
	{
		float Red, Green, Blue, Alpha;

		Color() : Red(0.f), Green(0.f), Blue(0.f), Alpha(1.f) {}
		Color(float R, float G, float B, float A) : Red(R), Green(G), Blue(B), Alpha(A) {}

		static Graphics::Color Black;
		static Graphics::Color White;
		static Graphics::Color Transparent;
		static Graphics::Color PureRed;
		static Graphics::Color Yellow;
		static Graphics::Color Orange;
		static Graphics::Color PureGreen;
		static Graphics::Color Cyan;
		static Graphics::Color PureBlue;
		static Graphics::Color Magenta;
		static Graphics::Color Purple;

		operator PString() const { return "Red[" + Types::ToString(Red) + "] Green[" + Types::ToString(Green) + "] Blue[" + Types::ToString(Blue) + "] Alpha[" + Types::ToString(Alpha) + "]"; }
		operator PString() { return "Red[" + Types::ToString(Red) + "] Green[" + Types::ToString(Green) + "] Blue[" + Types::ToString(Blue) + "] Alpha[" + Types::ToString(Alpha) + "]"; }
		operator NVGcolor() { return nvgRGBAf(Red, Green, Blue, Alpha); }
	};
}