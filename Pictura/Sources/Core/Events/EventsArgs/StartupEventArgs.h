#pragma once
#include "EventArgs.h"

namespace Pictura::Events
{
	class PICTURA_API StartupEventArgs : public EventArgs
	{
	public:
		StartupEventArgs(PVector<PString> arguments)
		{
			args = arguments;
		}

		~StartupEventArgs() {}

	public:
		PVector<PString> args;
	};
}