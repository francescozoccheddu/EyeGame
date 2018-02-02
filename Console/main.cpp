#include "../Platform/platform.hpp"
#include <iostream>
#include "../Platform/GL.h"

void render (float dt, int x, int y, Platform::Input in)
{
	std::cout << "x: " << x << " y: " << y << " fps: " << 1.0f/dt << std::endl;
	glClear (GL_COLOR_BUFFER_BIT);
	glClearColor (1, 0, 0, 1);
}

int main ()
{
	Platform::Window window;
	window.create ();
	window.run (&render);
	return 0;
}