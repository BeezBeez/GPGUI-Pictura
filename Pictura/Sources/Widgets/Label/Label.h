#pragma once
#include "Widgets/Widget.h"

using namespace Pictura::Graphics;

namespace Pictura::Widgets
{
	class PICTURA_API Label : public Widget
	{
	public:
		Label()
		{
			glGenBuffers(1, &m_VertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

			float vertices[3 * 3] = {
				-0.5f, -0.5f, 0.f,
				0.5f, -0.5f, 0.f,
				0.f, 0.5f, 0.f,
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glGenVertexArrays(1, &m_VertexArray);
			glBindVertexArray(m_VertexArray);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
			
			glGenBuffers(1, &m_IndexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			
			uint32 indices[3] = {
				0, 1, 2
			};

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

		virtual ~Label() {}

		NOTIFY_PROPERTY(PString, Text, OnTextChanged, "Label")
		PROPERTY(Color, TextColor, Color::Black)

	public:
		virtual void OnTextChanged(PString PreviousValue, PString NewValue) {}
		void Render() override
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}

	private:
		uint32 m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};
}