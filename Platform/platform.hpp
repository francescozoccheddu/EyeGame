#pragma once

struct GLFWwindow;

namespace Platform
{

	struct Input
	{
		float axisX;
		float axisY;
		bool fireRequested;
		bool jumping;
		float mouseX;
		float mouseY;
	};

	typedef void (*RenderFunc)(float deltaTime, int width, int height, Input input, void* userData);

	void initialize ();

	void terminate ();
	
	class Window
	{

	public:

		static const int minWidth;
		static const int minHeight;
		static const char *title;

		Window ();

		virtual ~Window ();

		void run (RenderFunc renderFunc, void* userData);

		void requestClose ();

		bool isRunning ();

		void create ();

		void destroy ();

	private:
		
		GLFWwindow* window;

	};

}