#pragma once
#include "Core/Core.h"

namespace Pictura::Maths
{
	struct Margin
	{
		float Top, Right, Bottom, Left;

		Margin(float UniformMargin)
		{
			Top = UniformMargin;
			Right = UniformMargin;
			Bottom = UniformMargin;
			Left = UniformMargin;
		}

		Margin(float Horizontal, float Vertical)
		{
			Right = Horizontal;
			Left = Horizontal;
			Top = Vertical;
			Bottom = Vertical;
		}

		Margin(float top, float Horizontal, float bottom)
		{
			Top = top;
			Bottom = bottom;
			Left = Horizontal;
			Right = Horizontal;
		}

		Margin(float top, float right, float bottom, float left)
		{
			Top = top;
			Right = right;
			Bottom = bottom;
			Left = left;
		}
	};
}