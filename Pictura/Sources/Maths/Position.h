#pragma once
#include "Core/Core.h"

namespace Pictura::Maths
{
	struct PPosition
	{
		float X, Y;

		PPosition() : X(0), Y(0) {}
		PPosition(float uniformPosition) : X(uniformPosition), Y(uniformPosition) {}
		PPosition(float x, float y) : X(x), Y(y) {}

		operator PString() const { return "X[" + Types::ToString(X) + "] Y[" + Types::ToString(Y) + "]"; }
		operator PString() { return "X[" + Types::ToString(X) + "] Y[" + Types::ToString(Y) + "]"; }
		bool operator!= (const PPosition& lhs)
		{
			return (this->X != lhs.X) || (this->Y != lhs.Y);
		}
	};
}