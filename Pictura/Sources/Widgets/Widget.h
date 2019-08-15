#pragma once
#include "Core/Core.h"
#include "Core/CoreException.h"
#include "Maths/Size.h"
#include "Maths/Position.h"
#include "Core/Events/Event.h"
#include "Core/Debug/Log.h"
#include "Threading/Thread.h"
#include "Core/Rendering/Graphics/Color.h"
#include "Core/Rendering/OpenGL/GLRenderer.h"
#include "Core/Rendering/Vulkan/VKRenderer.h"

namespace Pictura::Widgets
{
	class PICTURA_API Widget
	{
	public:
		enum class Visibility
		{
			Visible,
			Hidden
		};

	public:
		Widget() { }
		virtual ~Widget() { }

		NOTIFY_PROPERTY(Visibility, WidgetVisibility, OnVisibilityChanged, Visibility::Visible)
		NOTIFY_PROPERTY(Maths::PPosition, Position, OnPositionChanged, Maths::PPosition(0, 0))
		PROPERTY(PString, Name, "Widget");

	public:
		Event<void> Rendered;
		Event<Widget> Updated;
		Event<Visibility> VisibilityChanged;
		
	public:
		virtual void Update()
		{
			OnUpdate(*this);
		}

		virtual void Render()
		{

			OnRender();
		}

	public:
		virtual void OnRender() { Rendered(); }
		virtual void OnUpdate(Widget& widget) { Updated(widget); }
		virtual void OnVisibilityChanged(Visibility PreviousValue, Visibility NewValue) { VisibilityChanged(NewValue); }
		virtual void OnPositionChanged(Maths::PPosition PreviousValue, Maths::PPosition NewValue) { }
	};
}