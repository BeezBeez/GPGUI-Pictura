#pragma once
#include "Demo.h"

class DemoWindow : public Window
{
public:
	DemoWindow()
	{
		FontFamily::LoadFontByName("Arial", { "" }, *this);
		FontFamily::LoadFontByName("comic", { "" }, *this);

		Updated += EventHandler::Bind(&DemoWindow::DemoWindow_Updated, this);

		InitializeWidgets();
	}

	void InitializeWidgets()
	{
		SetSize(PSize(1024 / 1.5, 600 / 1.5));
		SetUseNativeWindowBorder(true);
		SetBackgroundColor(Color(.2, .2, .2, .7));

		Label1 = new Label();
		Label2 = new Label();
		DescriptionLabel = new Label();
		
		Children.Add(Label1);
		Label1->SetName("Label1");
		Label1->SetText("Welcome to Pictura demo !");
		Label1->SetTextSize(48.f);
		Label1->SetMargin(Margin(16));
		Label1->SetTextColor(Color::White);
		Label1->SetFont(FontFamily::GetFont("Arial", "", *Label1));
		Label1->SetDropShadow(Effects::DropShadowEffect(0.f, 4.f, 16.f));

		Children.Add(Label2);
		Label2->SetText("Presentation");
		Label2->SetTextSize(20.f);
		Label2->SetMargin(Margin(16, 64));
		Label2->SetTextColor(Color::White);
		Label2->SetFont(FontFamily::GetFont("Arial", "", *Label2));

		Children.Add(DescriptionLabel);
		DescriptionLabel->SetText("This is a sample text used to showcase text rendering features...");
		DescriptionLabel->SetTextSize(18.f);
		DescriptionLabel->SetMargin(Margin(16, 96));
		DescriptionLabel->SetTextColor(Color(1, 1, 1, .7f));
		DescriptionLabel->SetFont(FontFamily::GetFont("Arial", "", *DescriptionLabel));
	}

	float Pulse(float time)
	{
		return 0.5 * (1.f + sinf(time));
	}

	void DemoWindow_Updated(Widget& widget)
	{
		Window* wnd = (Window*)& widget;
		wnd->SetWindowOpacity(fmaxf(Pulse((float)glfwGetTime()), 0.01f));
		wnd->SetTitle("Width : " + Types::ToString(wnd->GetSize().Width) + " Height : " + Types::ToString(wnd->GetSize().Height) + " PixelRatio : " + Types::ToString(wnd->GetPixelRatio()) + " [FPS : " + Types::ToString(1000.f / GetFPS()) + "]");
	}

	Label* Label1;
	Label* Label2;
	Label* DescriptionLabel;
};