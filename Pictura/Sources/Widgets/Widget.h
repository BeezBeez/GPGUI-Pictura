#pragma once

#include "Core/Core.h"
#include "Core/CoreException.h"
#include "Core/System/Runtime.h"

#include "Maths/Size.h"
#include "Maths/Position.h"
#include "Maths/Margin.h"

#include "Core/Events/Event.h"
#include "Core/Debug/Log.h"
#include "Threading/Thread.h"

#include "Core/Rendering/Graphics/Color.h"
#include "Core/Rendering/Graphics/Effects.h"
#include "Core/Rendering/OpenGL/GLRenderer.h"
#include "Core/Rendering/Vulkan/VKRenderer.h"

#include "NanoVG/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "NanoVG/nanovg_gl.h"

using namespace Pictura::Maths;
using namespace Pictura::Threading;
using namespace Pictura::Graphics;

namespace Pictura::Widgets
{
	class PICTURA_API Window;
	class PICTURA_API Widget
	{
	public:
		enum class Visibility
		{
			Visible,
			Hidden
		};

		enum class HorizontalAlignment
		{
			Left,
			Center,
			Right,
			Fill
		};

		enum class VerticalAlignment
		{
			Top,
			Middle,
			Bottom,
			Fill
		};

	properties:
		NOTIFY_PROPERTY(Visibility, WidgetVisibility, OnVisibilityChanged, Visibility::Visible)
		NOTIFY_PROPERTY(Margin, Margin, OnMarginChanged, Margin(0))
		NOTIFY_PROPERTY(PSize, Size, OnSizeChanged, PSize(640, 480))
		NOTIFY_PROPERTY(Widgets::Widget*, ParentWidget, OnParentChanged, nullptr)

		PROPERTY(Widgets::Window*, OwnerWindow, nullptr)
		PROPERTY(PString, Name, "Widget");
		PROPERTY(HorizontalAlignment, HorizontalAlignment, HorizontalAlignment::Left)
		PROPERTY(VerticalAlignment, VerticalAlignment, VerticalAlignment::Top)

		READONLY_PROPERTY(uint64, Hash, -1)
		READONLY_PROPERTY(PPosition, Position, PPosition(0))
		READONLY_PROPERTY(PSize, WidgetSize, PSize(0, 0))

	public:
		Widget()
		{
			_Hash = std::hash<Widget*>{}(this);

			DEBUG_SECTION(
				Debug::Log::Trace("Widget hash = " + Types::ToString(Maths::Convert::ToHexadecimal(GetHash())));
			)
		}
		virtual ~Widget() { }

	events:
		Event<void> Initialized;
		Event<void> Rendered;
		Event<Widget> Updated;
		Event<Visibility> VisibilityChanged;
		Event<Widget*> ParentChanged;

	public:
		virtual void Update()
		{
			AlignWidget();

			OnUpdate(*this);
			Render();
		}

		virtual void Render()
		{
			if (!m_Initialized)
			{
				OnInitialize();
				m_Initialized = true;
			}
			else
			{
				OnRender();
			}
		}

	private:
		void AlignWidget()
		{
			_Position.X = 0;
			_Position.Y = 0;
			_WidgetSize.Width = GetSize().Width;
			_WidgetSize.Height = GetSize().Height;

			switch (GetHorizontalAlignment())
			{
			case HorizontalAlignment::Left:
				_Position.X = GetMargin().Left;
				_WidgetSize.Width = GetSize().Width;
				break;
			case HorizontalAlignment::Center:
				_Position.X = (((GetParentWidget()->GetSize().Width / 2.f) - (GetSize().Width / 2.f)) + GetMargin().Left - GetMargin().Right);
				_WidgetSize.Width = GetSize().Width;
				break;
			case HorizontalAlignment::Right:
				_Position.X = GetParentWidget()->GetSize().Width - GetSize().Width - GetMargin().Right;
				_WidgetSize.Width = GetSize().Width;
				break;
			case HorizontalAlignment::Fill:
				_Position.X = GetMargin().Left;
				_WidgetSize.Width = GetParentWidget()->GetSize().Width - GetMargin().Right - GetMargin().Left;
				break;
			default:
				_Position.X = 0;
				_WidgetSize.Width = GetSize().Width;
				break;
			}

			switch (GetVerticalAlignment())
			{
			case VerticalAlignment::Top:
				_Position.Y = GetMargin().Top;
				_WidgetSize.Height = GetSize().Height;
				break;
			case VerticalAlignment::Middle:
				_Position.Y = ((GetParentWidget()->GetSize().Height / 2) - (GetSize().Height / 2)) + (GetMargin().Top - GetMargin().Bottom);
				_WidgetSize.Height = GetSize().Height;
				break;
			case VerticalAlignment::Bottom:
				_Position.Y = GetParentWidget()->GetSize().Height - GetSize().Height - GetMargin().Bottom;
				_WidgetSize.Height = GetSize().Height;
				break;
			case VerticalAlignment::Fill:
				_Position.Y = GetMargin().Top;
				_WidgetSize.Height = GetParentWidget()->GetSize().Height - GetMargin().Bottom - GetMargin().Top;
				break;
			default:
				_Position.Y = 0;
				_WidgetSize.Height = GetSize().Height;
				break;
			}
		}

	private:
		bool m_Initialized = false;

	public:
		virtual void OnInitialize() { Initialized(); }
		virtual void OnRender() { Rendered(); }

		virtual void OnUpdate(Widget& widget)
		{
			Updated(widget);
		}
		virtual void OnVisibilityChanged(Visibility PreviousValue, Visibility NewValue) { VisibilityChanged(NewValue); }
		virtual void OnPositionChanged(Maths::PPosition PreviousValue, Maths::PPosition NewValue) { }
		virtual void OnParentChanged(Widget* PreviousValue, Widget* NewValue) { ParentChanged(NewValue); }

		virtual void OnMarginChanged(Margin NewValue, Margin PreviousValue)
		{

		}

		virtual void OnSizeChanged(PSize PreviousValue, PSize NewValue)
		{
			
		}


	};
}