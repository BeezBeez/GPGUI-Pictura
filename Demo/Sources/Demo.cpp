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
		SetRenderer(Renderer::RendererType::OpenGL, false);

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