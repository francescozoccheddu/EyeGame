#include "world.h"
#include "../Platform/GL.h"
#include <fstream>
#include <iostream>

#define LOAD_SHADER(name, type) _TEST_createShaderFromSourceFile(R"(C:\Users\zocch\OneDrive\Projects\EyeGame\EyeGame\Gameplay\)" name ".glsl", type)

GLuint createShaderFromSource (const char * source, GLenum shaderType)
{
	GLuint shader = 0;
	std::cout << source << std::endl;
	return shader;
}

GLuint _TEST_createShaderFromSourceFile (const char * filename, GLenum shaderType)
{
	std::ifstream file;
	file.open (filename);
	file.seekg (0, std::ios::end);
	size_t size = file.tellg ();
	std::string buffer (size, ' ');
	file.seekg (0);
	file.read (&buffer[0], size);
	return createShaderFromSource (buffer.data(), shaderType);
}


World::World (Platform::Window *window) : window(window)
{
	LOAD_SHADER ("default_vertex", GL_VERTEX_SHADER);
}


World::~World ()
{
}



void World::run ()
{
	window->run (&World::renderFunc, this);
}

void World::render (float deltaTime, int width, int height, Platform::Input input)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glClearColor (1, 0, 0, 1);
}

void World::renderFunc (float deltaTime, int width, int height, Platform::Input input, void * userData)
{
	World *world = reinterpret_cast<World*>(userData);
	world->render (deltaTime, width, height, input);
}
