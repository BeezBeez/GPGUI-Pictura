#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;
using namespace Pictura::Graphics;
using namespace Pictura::Widgets;
using namespace Pictura::Threading;

class MyWindow : public Window
{
public:
	MyWindow()
	{
		Size.Width = 400;
		Size.Height = 400;
		Title = "My custom window";
		Shown += EventHandler::Bind(&MyWindow::MyWindow_Shown, this);
		//Closed += EventHandler::Bind(&MyWindow::MyWindow_Closed, this);
	}

	~MyWindow()
	{
		
	}

	void MyWindow_Shown()
	{
		Debug::Log::Trace("Hello MyWindow !");
	}

	void MyWindow_Closed()
	{
		Debug::Log::Trace("Bye MyWindow !");
		Application::CurrentApplication->Exit();
	}
};

class DemoApplication : public Application
{
public:
	void OnApplicationStart(StartupEventArgs& e) override
	{
		Application::OnApplicationStart(e);
		
		ApplicationCloseBehavior = CloseBehavior::OnMainWindowClose;
		SetRenderer(Renderer::RendererType::Vulkan, false);
		
		MainWindow = new MyWindow();
		MainWindow->Show();

		Thread::Delay(5000);

		for (int i = 0; i < 2; i++)
		{
			auto wnd = new Window();
			wnd->Title = "Window number " + Types::ToString(i);
			wnd->Show();
		}

		Thread::Delay(1500);
		MainWindow->Hide();

		Thread::Delay(2000);
		MainWindow->Show();

		Console::Pause();
	}

	void OnApplicationClose() override
	{
		Application::OnApplicationClose();
		Log::Trace("Application closed !");
	}
};
APPLICATION(DemoApplication)