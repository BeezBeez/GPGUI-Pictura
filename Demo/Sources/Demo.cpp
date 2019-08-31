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
	DemoApplication()
	{
		ApplicationStart += EventHandler::Bind(&DemoApplication::DemoApplication_ApplicationStart, this);
		ApplicationClose += EventHandler::Bind(&DemoApplication::DemoApplication_ApplicationClose, this);
	}

	void DemoApplication_ApplicationStart(StartupEventArgs& e)
	{
		ApplicationCloseBehavior = CloseBehavior::OnLastWindowClose;
		SetRenderer(Renderer::RendererType::OpenGL, true);

		MainWindow = new Window();
		MainWindow->SetSize(PSize(1280, 720));
		MainWindow->SetWindowState(Window::WindowState::Normal);
		MainWindow->SetUseNativeWindowBorder(true);
		MainWindow->SetTitle("Test window");
		MainWindow->Rendered += EventHandler::Bind(&DemoApplication::MainWindow_Rendered, this);

		auto wnd = new Window();
		wnd->SetSize(PSize(640, 480));
		wnd->SetTitle("Another window");
		wnd->Rendered += EventHandler::Bind(&DemoApplication::wnd_Rendered, this);

		Label* Label1 = new Label();
		Label1->SetName("Label1");
		Label1->SetTextColor(Color::PureRed);

		MainWindow->Show();
		wnd->Show();
		MainWindow->AddWidget(Label1);
	}

	void DemoApplication_ApplicationClose()
	{
		Log::Trace("Application closed !");
	}

	void MainWindow_Rendered()
	{
		CurrentRenderer->ClearColor(Color(.07f, .07f, .07f, 1.f));
	}

	void wnd_Rendered()
	{
		CurrentRenderer->ClearColor(Color::PureBlue);
	}

};
APPLICATION(DemoApplication)