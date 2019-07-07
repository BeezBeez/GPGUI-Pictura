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
		Runtime::ForceExitApplication();
	}
};

class DemoApplication : public Application
{
public:
	void OnApplicationStart(StartupEventArgs& e) override
	{
		Application::OnApplicationStart(e);

		SetRenderer(Renderer::RendererType::Vulkan, false);

		auto defaultWnd = new MyWindow();
		defaultWnd->Show();

		Thread::Delay(2000);

		auto anotherWnd = new Window();
		anotherWnd->Size.Width = 1024;
		anotherWnd->Size.Height = 600;
		anotherWnd->Title = "Another window !";
		anotherWnd->Show();

		Console::Pause();
	}

	void OnApplicationClose() override
	{
		Application::OnApplicationClose();
		Log::Trace("Application closed !");
	}
};
APPLICATION(DemoApplication)