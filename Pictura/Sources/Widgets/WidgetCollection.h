#pragma once
#include "Core/Core.h"
#include "Widget.h"

namespace Pictura::Widgets
{
	class PICTURA_API WidgetCollection
	{
	public:
		WidgetCollection()
		{
			parentWidget = nullptr;
			ownerWindow = nullptr;
		}

		WidgetCollection(Widget* ParentWidget, Window* OwnerWindow)
		{
			parentWidget = ParentWidget;
			ownerWindow = OwnerWindow;
		}

		PVector<Widget*> Get()
		{
			return collection;
		}

		void Add(Widget* widget)
		{
			widget->SetOwnerWindow(ownerWindow);
			widget->SetParentWidget(parentWidget);
			collection.push_back(widget);
		}

		void Remove(Widget* widget)
		{
			Types::Vectors::RemoveElement<Widget*>(collection, widget);
			delete widget;
		}

		void Update()
		{
			for (auto widget : collection)
			{
				widget->Update();
			}
		}

	public:
		WidgetCollection& operator=(std::initializer_list<Widget*> widgetList)
		{
			WidgetCollection wc;
			wc.collection = widgetList;
		}

	private:
		PVector<Widget*> collection;
		Widget* parentWidget;
		Window* ownerWindow;
	};
}