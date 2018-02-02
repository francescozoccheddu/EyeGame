#include "platform.hpp"
#include <stdexcept>
#include <chrono>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

bool glLoaded;

void Platform::initialize ()
{
	glfwInit ();
}

void Platform::terminate ()
{
	glfwTerminate ();
}

Platform::Window::Window () : window(nullptr)
{
}

Platform::Window::~Window ()
{
	destroy ();
}

void Platform::Window::run (RenderFunc renderFunc, void* userData)
{
	if (!window || !renderFunc)
	{
		return;
	}

	glfwSetWindowShouldClose (window, GLFW_FALSE);

	auto lastTime = std::chrono::high_resolution_clock::now ();
	while (window && !glfwWindowShouldClose (window))
	{
		auto currentTime = std::chrono::high_resolution_clock::now ();
		
		Input input = {};
		int width, height;
		glfwGetFramebufferSize (window, &width, &height);

		std::chrono::duration<float> deltaTime = currentTime - lastTime;
		renderFunc (deltaTime.count(), width, height, input, userData);
		
		lastTime = currentTime;

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}
}

void Platform::Window::requestClose ()
{
	if (window)
	{
		glfwSetWindowShouldClose (window, GLFW_TRUE);
	}
}

void Platform::Window::create ()
{
	if (window)
	{
		return;
	}

	initialize ();

	window = glfwCreateWindow (640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		throw std::runtime_error ("Failed to create window");
	}

	glfwMakeContextCurrent (window);

	glfwSwapInterval (2);

	if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error ("Failed to load OpenGL");
	}
}

void Platform::Window::destroy ()
{
	if (window)
	{
		glfwDestroyWindow (window);
		window = nullptr;
	}
}

bool Platform::Window::isRunning ()
{
	return window != nullptr;
}

const int Platform::Window::minWidth = 20;
const int Platform::Window::minHeight = 20;
const char* Platform::Window::title = "EyeGame";
