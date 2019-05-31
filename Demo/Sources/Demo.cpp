#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

class DemoApplication : public Application
{
public:
	virtual void OnApplicationStart(StartupEventArgs& e) override
	{
		Log::Trace("Application started !");
		std::getchar();
	}


	virtual void OnApplicationClose() override
	{
		Log::Trace("Application closed !");
		std::getchar();
	}
};
APPLICATION(DemoApplication)