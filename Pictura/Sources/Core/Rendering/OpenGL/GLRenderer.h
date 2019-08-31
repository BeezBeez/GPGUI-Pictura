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

			int version = gladLoadGL(glfwGetProcAddress);
			if (version == 0) {
				throw RendererException("Failed to load OpenGL drivers !");
			}
			
			if (ShowDebugMessage)
			{
				glEnable(GL_DEBUG_OUTPUT);
				glDebugMessageCallback(GLErrorCallback, 0);
				gladSetGLPostCallback(DebugPostCallback);
				Debug::Log::Trace("OpenGL Renderer informations :", "OPENGL");
				Debug::Log::Trace("		- Version : " + Types::ToString(glGetString(GL_VERSION)), "OPENGL");
				Debug::Log::Trace("		- Vendor : " + Types::ToString(glGetString(GL_VENDOR)), "OPENGL");
				Debug::Log::Trace("		- Renderer : " + Types::ToString(glGetString(GL_RENDERER)), "OPENGL");
				Debug::Log::Trace("		- Shading Language Version : " + Types::ToString(glGetString(GL_SHADING_LANGUAGE_VERSION)), "OPENGL");
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
		void MakeContextCurrent() override
		{
			glfwMakeContextCurrent((GLFWwindow*)GetRendererUserData());
		}

		void SwapBuffers() override
		{
			glfwSwapBuffers((GLFWwindow*)GetRendererUserData());
		}

		void ClearColor(Color color) override
		{
			glClearColor(color.Red, color.Green, color.Blue, color.Alpha);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void CreateViewport(Maths::PPosition position, Maths::PSize size) override
		{
			glViewport(position.X, position.Y, size.Width, size.Height);
		}

	private:
		static void ErrorCallback(int error, const char* description)
		{
			throw InvalidOperationException("RenderingFramework Error : " + Types::ToString(description));
		}

		static void DebugPostCallback(void* ret, const char* name, GLADapiproc apiproc, int len_args, ...)
		{
			Debug::Log::Info("OPENGL_CALL : " + Types::ToString(name), "OPENGL DEBUG");
			CheckOpenGLError(name, "NOT SPECIFIED", -1);
		}

		static void CheckOpenGLError(const char* stmt, const char* fname, int line)
		{
			GLenum err = glad_glGetError();
			PString errType, errMsg;

			switch (err)
			{
			case GL_NO_ERROR:
			{
				errType = "NO ERROR";
				errMsg = "NO ERROR MESSAGE";
				break;
			}
			case GL_INVALID_ENUM:
			{
				errType = "INVALID ENUM";
				errMsg = "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
			case GL_INVALID_VALUE:
			{
				errType = "INVALID VALUE";
				errMsg = "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
			case GL_INVALID_OPERATION:
			{
				errType = "INVALID OPERATION";
				errMsg = "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
			case GL_INVALID_FRAMEBUFFER_OPERATION:
			{
				errType = "INVALID FRAMEBUFFER OPERATION";
				errMsg = "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
			case GL_OUT_OF_MEMORY:
			{
				errType = "OUT OF MEMORY";
				errMsg = "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
				break;
			}
			case GL_STACK_UNDERFLOW:
			{
				errType = "STACK UNDERFLOW";
				errMsg = "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
				break;
			}
			case GL_STACK_OVERFLOW:
			{
				errType = "STACK OVERFLOW";
				errMsg = "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
				break;
			}
			default:
			{
				errType = "UNKNOWN ERROR";
				errMsg = "Unknown error...";
				break;
			}
			}

			if (err != GL_NO_ERROR)
			{
				Debug::Log::Error("OpenGL Runtime Error -- ");
				Debug::Log::Error("		ErrorType : " + errType);
				Debug::Log::Error("		ErrorMessage : " + errMsg);
				Debug::Log::Error("		Command : " + Types::ToString(stmt));
				Debug::Log::Error("		File : " + Types::ToString(fname));
				Debug::Log::Error("		Line : " + Types::ToString(line));
				throw RendererException("Renderer has stopped working...");
			}
		}

		static void GLAPIENTRY GLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			Debug::Log::Error("OpenGL Error : " + (PString)message);
		}

	public:
		int MajorVersion;
		int MinorVersion;
	};
}