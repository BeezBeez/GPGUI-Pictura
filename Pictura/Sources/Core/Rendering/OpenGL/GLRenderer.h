#pragma once
#include "Core/Rendering/Renderer.h"
#include "glad/gl.h"
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
			if (glfwInit() != 1) {
				throw RendererException("Failed to initialize OpenGL !");
			}

			glfwWindowHint(GLFW_VISIBLE, 0);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MajorVersion);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MinorVersion);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			GLFWwindow* initWindow = glfwCreateWindow(640, 480, "Initialization window", nullptr, nullptr);
			glfwMakeContextCurrent(initWindow);

			GL = (GladGLContext*)malloc(sizeof(GladGLContext));
			if (!GL) {
				throw RendererException("Failed to allocate memory for an OpenGL context !");
			}

			int version = gladLoadGLContext(GL, glfwGetProcAddress);
			if (version == 0) {
				throw RendererException("Failed to create an OpenGL context !");
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
		}

		void Destroy()
		{

		}

		void CreateCommandPool()
		{

		}

		void CreateCommandBuffer()
		{

		}
	public:
		GladGLContext* GL = nullptr;
		int MajorVersion;
		int MinorVersion;
	};
}