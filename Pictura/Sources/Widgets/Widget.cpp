#include "PicturaPCH.h"
#include "Widget.h"
#include "Window/Window.h"

namespace Pictura::Widgets
{
	bool Widget::HitTest()
	{
		prevCurPos = curPos;
		curPos = GetOwnerWindow()->CursorPosition;

		return Types::Numbers::IsBetween(curPos.X, GetPosition().X, GetPosition().X + GetSize().Width) && Types::Numbers::IsBetween(curPos.Y, GetPosition().Y, GetPosition().Y + GetSize().Height);
	}
}