#pragma once
#include "Widgets/Widget.h"
#include "Core/Rendering/Text/FontFamily.h"

using namespace Pictura::Graphics;
using namespace Pictura::Graphics::Text;

namespace Pictura::Widgets
{
	class PICTURA_API Label : public Widget
	{
	properties:
		NOTIFY_PROPERTY(PString, Text, OnTextChanged, "Label")
		READONLY_PROPERTY(PString, FontName, "comic")
		READONLY_PROPERTY(PString, FontWeight, "")
		PROPERTY(int, Font, -1)
		PROPERTY(Color, TextColor, Color::Black)
		PROPERTY(float, TextSize, 12.f)
		PROPERTY(float, TextBlur, 0.f)
		PROPERTY(Color, DropShadowColor, Color::Black)
		PROPERTY(Effects::DropShadowEffect, DropShadow, Effects::DropShadowEffect(0.f, 0.f, 0.f))

	public:
		Label()
		{
			Initialized += EventHandler::Bind(&Label::Label_OnInitialize, this);
			Rendered += EventHandler::Bind(&Label::Label_Render, this);
			Updated += EventHandler::Bind(&Label::Label_Update, this);
		}

		void Label_OnInitialize()
		{
			if (GetFont() == -1) {
				SetFont(FontFamily::GetFont(GetFontName(), GetFontWeight(), *this));
			}
		}

		void Label_Update(Widget& widget)
		{
			nvgFontFaceId(GetOwnerWindow()->GetBrush(), GetFont());
			nvgFontSize(GetOwnerWindow()->GetBrush(), GetTextSize());
			nvgTextAlign(GetOwnerWindow()->GetBrush(), NVG_ALIGN_LEFT | NVG_ALIGN_TOP);

			float h;
			float bounds[4];
			nvgTextBounds(GetOwnerWindow()->GetBrush(), GetPosition().X, GetPosition().Y, GetText().c_str(), NULL, bounds);
			nvgTextMetrics(GetOwnerWindow()->GetBrush(), NULL, NULL, &h);
			SetSize(PSize(roundf(bounds[2] - bounds[0]), bounds[3] - bounds[1]));

			nvgFontBlur(GetOwnerWindow()->GetBrush(), GetDropShadow().BlurSize);
			nvgFillColor(GetOwnerWindow()->GetBrush(), GetDropShadowColor());
		}

		void Label_Render()
		{
			if (GetDropShadow().OffsetX != 0 || GetDropShadow().OffsetY != 0)
			{
				nvgText(GetOwnerWindow()->GetBrush(), GetPosition().X + GetDropShadow().OffsetX, GetPosition().Y + GetDropShadow().OffsetY, GetText().c_str(), NULL);
			}

			nvgFontBlur(GetOwnerWindow()->GetBrush(), GetTextBlur());
			nvgFillColor(GetOwnerWindow()->GetBrush(), GetTextColor());
			nvgText(GetOwnerWindow()->GetBrush(), GetPosition().X, GetPosition().Y, GetText().c_str(), NULL);
			//TODO : Remove widget size system to prefer automatic size computing instead
		}

		virtual ~Label() {}

	public:
		virtual void OnTextChanged(PString PreviousValue, PString NewValue) {}

	};
}