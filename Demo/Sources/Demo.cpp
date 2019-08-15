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
		MainWindow->SetSize(PSize(1024, 600));
		MainWindow->SetWindowState(Window::WindowState::Normal);
		MainWindow->SetUseNativeWindowBorder(true);
		MainWindow->SetTitle("Test window");
		MainWindow->Updated += EventHandler::Bind(&DemoApplication::MainWindow_Updated, this);

		MainWindow->Show();

		Label* Label1 = new Label();
		Label1->SetName("Label1");
		Label1->SetTextColor(Color::White);
		MainWindow->AddWidget(Label1);

		auto AnotherWindow = new Window();
		AnotherWindow->SetSize(PSize(800, 600));
		AnotherWindow->SetTitle("Another window");
		AnotherWindow->Updated += EventHandler::Bind(&DemoApplication::AnotherWnd_Updated, this);
		AnotherWindow->Show();
	}

	void DemoApplication_ApplicationClose()
	{
		Log::Trace("Application closed !");
	}

	void MainWindow_Updated(Widget& widget)
	{
		CurrentRenderer->ClearColor(Color(.07f, .07f, .07f, 1.f));
	}

	void AnotherWnd_Updated(Widget& widget)
	{
		CurrentRenderer->ClearColor(Color(.75f, .75f, .75f, 1.f));
	}
};
APPLICATION(DemoApplication)