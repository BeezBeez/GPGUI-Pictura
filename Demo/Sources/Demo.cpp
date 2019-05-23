#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

class DemoApplication : public Application
{
public:
	DemoApplication()
	{

	}

	void Run() override
	{
		Application::Run();
		Log::Trace("Salut toi!");
	}

private:

};

/** MOVE ENTRY POINT TO EXTERNAL HEADER IN PICTURA FRAMEWORK **/
int main()
{
	DemoApplication app = DemoApplication();
	app.Run();
}