#pragma once
#include "Core/Core.h"
#include "Core/CoreException.h"
#include "Maths/Size.h"
#include "Core/Events/Event.h"
#include "Core/Debug/Log.h"
#include "Threading/Thread.h"
#include "Core/Rendering/OpenGL/GLRenderer.h"
#include "Core/Rendering/Vulkan/VKRenderer.h"

using namespace Pictura::Maths;
using namespace Pictura::Threading;

namespace Pictura::Widgets
{
	class PICTURA_API Window
	{
	public:
		Window();
		virtual ~Window();
		
		NOTIFY_PROPERTY(PSize, Size, OnSizeChanged)
		PROPERTY(PString, Title)

	public:
		Event<void> Shown;
		Event<void> Closed;
		Event<void> Updated;
		Event<void> Resized;
		Event<void> SizeChanged;

		void Show();
		void Update();
		void Close();

	protected:
		virtual void OnShow() { }
		virtual void OnClose() { }
		virtual void OnUpdate() { }
		virtual void OnResize() { }
		virtual void OnSizeChanged(const PSize& oldValue, const PSize& newValue)
		{
			Debug::Log::Trace("Previous size = " + (PString)oldValue);
			Debug::Log::Trace("New size = " + (PString)newValue);
		}
	};
}