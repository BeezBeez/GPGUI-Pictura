#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

class DemoApplication : public Application
{
public:
	
	void OnApplicationStart(StartupEventArgs& e) override
	{
		Log::Trace("Application started !");
		Log::Trace("Application arguments : ");
		int i = 0;
		for (PString arg : e.args)
		{
			Log::Trace("[" + Types::ToString(i) + "] : " + arg);
			i++;
		}
		std::getchar();
	}

	void OnApplicationClose() override
	{
		Log::Trace("Application closed !");
		std::getchar();
	}
};
APPLICATION(DemoApplication)