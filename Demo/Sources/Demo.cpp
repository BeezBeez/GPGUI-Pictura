#include "PicturaMain.h"

#include "Demo.h"
#include "AppWindow.h"

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

		MainWindow = new DemoWindow();
		MainWindow->Show();

		Runtime::SetShowWidgetsLimits(true),

		Thread::Delay(1000);
		CastTo<DemoWindow*>(MainWindow)->Label1->SetHorizontalAlignment(Widget::HorizontalAlignment::Center);
		CastTo<DemoWindow*>(MainWindow)->Label1->SetVerticalAlignment(Widget::VerticalAlignment::Middle);
		CastTo<DemoWindow*>(MainWindow)->Label2->SetHorizontalAlignment(Widget::HorizontalAlignment::Center);
		CastTo<DemoWindow*>(MainWindow)->DescriptionLabel->SetHorizontalAlignment(Widget::HorizontalAlignment::Center);
	}

	void DemoApplication_ApplicationClose()
	{
		Log::Trace("Application closed !");
	}

};
APPLICATION(DemoApplication)