#pragma once
#include "Core/Core.h"

namespace Pictura::Maths
{
	struct PPosition
	{
		uint32 X, Y;

		PPosition() : X(0), Y(0) {}
		PPosition(uint32 x, uint32 y) : X(x), Y(y) {}

		operator PString() const { return "X[" + Types::ToString(X) + "] Y[" + Types::ToString(Y) + "]"; }
		operator PString() { return "X[" + Types::ToString(X) + "] Y[" + Types::ToString(Y) + "]"; }
	};
}