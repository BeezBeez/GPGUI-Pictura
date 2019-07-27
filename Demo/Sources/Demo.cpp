#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;
using namespace Pictura::Graphics;
using namespace Pictura::Widgets;
using namespace Pictura::Threading;

class DemoApplication : public Application
{
public:
	void OnApplicationStart(StartupEventArgs& e) override
	{
		Application::OnApplicationStart(e);
		
		ApplicationCloseBehavior = CloseBehavior::OnMainWindowClose;
		PString mode = File::Read("C:\Renderer.txt");
		Renderer::RendererType RMode = (mode == "OpenGL" ? Renderer::RendererType::OpenGL : mode == "Vulkan" ? Renderer::RendererType::Vulkan : Renderer::RendererType::Null);
		SetRenderer(RMode, true);

		MainWindow = new Window();
		MainWindow->SetSize(PSize(640, 480));

		Console::Pause();
	}

	void OnApplicationClose() override
	{
		Application::OnApplicationClose();
		Log::Trace("Application closed !");
	}
};
APPLICATION(DemoApplication)