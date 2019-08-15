#pragma once
#include "Core/Rendering/Renderer.h"
#include "GLFW/glfw3.h"

namespace Pictura::Graphics::OpenGL
{
	class PICTURA_API GLRenderer final : public Renderer
	{
	public:
		GLRenderer(int Major, int Minor)
		{ 
			MajorVersion = Major;
			MinorVersion = Minor;
		}

		virtual ~GLRenderer() { }

		void Init() override
		{
			glfwSetErrorCallback(&GLRenderer::ErrorCallback);
			if (glfwInit() != 1) {
				throw RendererException("Failed to initialize RenderingFramework !");
			}

			glfwWindowHint(GLFW_VISIBLE, 0);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MajorVersion);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MinorVersion);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			GLFWwindow* initWindow = glfwCreateWindow(640, 480, "Initialization window", nullptr, nullptr);
			glfwMakeContextCurrent(initWindow);

			GL = (GladGLContext*)malloc(sizeof(GladGLContext));
			if (!GL) {
				throw MemoryException("Failed to allocate memory for an OpenGL context !");
			}

			int version = gladLoadGLContext(GL, glfwGetProcAddress);
			if (version == 0) {
				throw RendererException("Failed to load OpenGL drivers !");
			}
			
			if (ShowDebugMessage)
			{
				Debug::Log::Trace("OpenGL Renderer informations :", "OPENGL");
				Debug::Log::Trace("		- Version : " + Types::ToString(GL->GetString(GL_VERSION)), "OPENGL");
				Debug::Log::Trace("		- Vendor : " + Types::ToString(GL->GetString(GL_VENDOR)), "OPENGL");
				Debug::Log::Trace("		- Renderer : " + Types::ToString(GL->GetString(GL_RENDERER)), "OPENGL");
				Debug::Log::Trace("		- Shading Language Version : " + Types::ToString(GL->GetString(GL_SHADING_LANGUAGE_VERSION)), "OPENGL");
			}
			Debug::Log::Success("OpenGL Renderer created successfully !", "RENDERER");

			glfwDestroyWindow(initWindow);
		}

		void Destroy() override
		{

		}

		void CreateCommandPool() override
		{

		}

		void CreateCommandBuffer() override
		{

		}

	public:
		void ClearColor(Color color) override
		{
			GL->Clear(GL_COLOR_BUFFER_BIT);
			GL->ClearColor(color.Red, color.Green, color.Blue, color.Alpha);
		}

		void CreateViewport(Maths::PPosition position, Maths::PSize size) override
		{
			GL->Viewport(position.X, position.Y, size.Width, size.Height);
		}

		void SwapBuffers() override
		{

		}

	private:
		static void ErrorCallback(int error, const char* description)
		{
			throw InvalidOperationException("RenderingFramework Error : " + Types::ToString(description));
		}

		GladGLContext* GL = nullptr;
	public:
		int MajorVersion;
		int MinorVersion;
	};
}