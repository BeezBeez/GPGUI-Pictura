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
			auto ctx = Application::GetOpenGLRenderer()->GL;

			ctx->GenVertexArrays(1, &m_VertexArray);
			ctx->BindVertexArray(m_VertexArray);

			ctx->GenBuffers(1, &m_VertexBuffer);
			ctx->BindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

			float vertices[3 * 3] = {
				-0.5f, -0.5f, 0.f,
				0.5f, -0.5f, 0.f,
				0.f, 0.5f, 0.f,
			};

			ctx->BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			ctx->EnableVertexAttribArray(0);
			ctx->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

			ctx->GenBuffers(1, &m_IndexBuffer);
			ctx->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
			
			uint32 indices[3] = {
				0, 1, 2
			};

			ctx->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}

		virtual ~Label() {}

		NOTIFY_PROPERTY(PString, Text, OnTextChanged, "Label")
		PROPERTY(Color, TextColor, Color::Black)

	public:
		virtual void OnTextChanged(PString PreviousValue, PString NewValue) {}
		void Render() override
		{
			Application::GetOpenGLRenderer()->GL->Clear(GL_COLOR_BUFFER_BIT);
			Application::GetOpenGLRenderer()->GL->BindVertexArray(m_VertexArray);
			Application::GetOpenGLRenderer()->GL->DrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		}

	private:
		uint32 m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};
}