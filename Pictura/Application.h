#pragma once
namespace Pictura
{
	class PICTURA_API Application
	{
		enum class Renderer
		{
			OpenGL,
			DirectX11,
			DirectX12,
			Vulkan
		};

	public:
		Application();
		~Application();
	private:
		static Renderer sRenderer;
	public:
		virtual const void Main() = 0;

		static void SetRenderer(Application::Renderer RendererType);
	};
}
