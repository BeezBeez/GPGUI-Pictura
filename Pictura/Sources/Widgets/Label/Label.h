#pragma once
#include "Widgets/Widget.h"

using namespace Pictura::Graphics;

namespace Pictura::Widgets
{
	class PICTURA_API Label : public Widget
	{
	public:
		Label() {}
		virtual ~Label() {}

		NOTIFY_PROPERTY(PString, Text, OnTextChanged, "Label")
		PROPERTY(Color, TextColor, Color::Black)

	public:
		virtual void OnTextChanged(PString PreviousValue, PString NewValue) {}
		void Render() override
		{

		}
	};
}