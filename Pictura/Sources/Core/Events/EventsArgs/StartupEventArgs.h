#pragma once
#include "EventArgs.h"
#include "Core\System\Runtime.h"

namespace Pictura::Events
{
	class PICTURA_API StartupEventArgs : public EventArgs
	{
	public:
		inline StartupEventArgs()
		{
			args = Runtime::Arguments;
		}
		~StartupEventArgs();

	private:
		PVector<PString> args;
	};

	StartupEventArgs::~StartupEventArgs()
	{
	}
}