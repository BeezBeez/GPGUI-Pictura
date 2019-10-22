#pragma once
#include "Core/Rendering/Context.h"
#include "Core/Exceptions/RendererException.h"

namespace Pictura::Graphics::OpenGL
{
	class PICTURA_API GLContext final : public Context
	{
	public:
		void Init(bool Debug) override
		{
			glfwWindowHint(GLFW_VISIBLE, 0);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			GLFWwindow* initWindow = glfwCreateWindow(640, 480, "Initialization window (context)", nullptr, nullptr);
			glfwMakeContextCurrent(initWindow);

			context = (GladGLContext*)malloc(sizeof(GladGLContext));
			if (!context) return;
			int version = gladLoadGLContext(context, glfwGetProcAddress);
			if (version == 0) {
				throw RendererException("Failed to load OpenGL drivers !");
			}

			DEBUG_SECTION(
				Debug::Log::Trace("Creating OpenGL " + Types::ToString(glGetString(GL_VERSION)) + " Context...", "OPENGL");
			)
			if (Debug) {
				glEnable(GL_DEBUG_OUTPUT);
				glDebugMessageCallback(GLErrorCallback, 0);
			}

			SetPtr(context);
			gladSetGLContext(context);
		}
	private:
		GladGLContext* context;
		static void GLAPIENTRY GLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			PString msgSource = "Unknown";
			switch (source)
			{
				case GL_DEBUG_SOURCE_API:
				{
					msgSource = "OpenGL API";
					break;
				}
				case GL_DEBUG_SOURCE_APPLICATION:
				{
					msgSource = "Application";
					break;
				}
				case GL_DEBUG_SOURCE_OTHER:
				{
					msgSource = "Other";
					break;
				}
				case GL_DEBUG_SOURCE_SHADER_COMPILER:
				{
					msgSource = "Shader Compiler";
					break;
				}
				case GL_DEBUG_SOURCE_THIRD_PARTY:
				{
					msgSource = "Third-Party";
					break;
				}
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				{
					msgSource = "Window-system API";
					break;
				}
				default:
				{
					break;
				}
			}


			switch (severity)
			{
				case GL_DEBUG_SEVERITY_NOTIFICATION:
				{
					Debug::Log::Trace("OpenGL Notification [SOURCE->" + msgSource + "] : " + (PString)message, "OPENGL DEBUG");
					break;
				}
				case GL_DEBUG_SEVERITY_LOW:
				{
					Debug::Log::Info("OpenGL Info [SOURCE->" + msgSource + "] : " + (PString)message, "OPENGL DEBUG");
					break;
				}
				case GL_DEBUG_SEVERITY_MEDIUM:
				{
					Debug::Log::Warning("OpenGL Warning [SOURCE->" + msgSource + "] : " + (PString)message, "OPENGL DEBUG");
					break;
				}
				case GL_DEBUG_SEVERITY_HIGH:
				{
					Debug::Log::Error("OpenGL Error [SOURCE->" + msgSource + "] : " + (PString)message, "OPENGL DEBUG");
					break;
				}
				default:
				{
					Debug::Log::Trace("OpenGL Message [SOURCE->" + msgSource + "] (Unknown severity) : " + (PString)message, "OPENGL DEBUG");
					break;
				}
			}
		}
	};
}