#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;
using namespace Pictura::Graphics;

class DemoApplication : public Application
{
public:
	
	void OnApplicationStart(StartupEventArgs& e) override
	{
		Application::OnApplicationStart(e);
		SetRenderer(Renderer::RendererType::Vulkan, true);
		std::getchar();
	}

	void OnApplicationClose() override
	{
		Application::OnApplicationClose();
		Log::Trace("Application closed !");
	}
};
APPLICATION(DemoApplication)