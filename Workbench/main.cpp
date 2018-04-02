#include <stdexcept>
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Camera.hpp"
#include "CircularSectorMesh.hpp"
#include "PawnRenderer.h"
#include "Pawn.h"
#include "../c4d2c/C4D2C.h"

#define LOAD_SHADER(name, type) _TEST_createShaderFromSourceFile(R"(C:\Users\zocch\Documents\Visual Studio 2017\Projects\EyeGame\EyeGame\Workbench\)" name ".glsl", type)

GLuint createShaderFromSource (const char * source, GLenum shaderType)
{
	GLuint shader = glCreateShader (shaderType);
	if (shader == 0)
	{
		throw std::runtime_error ("Failed to create shader");
	}

	glShaderSource (shader, 1, &source, NULL);
	glCompileShader (shader);
	GLint compileStatus;
	glGetShaderiv (shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		char infoLog[512];
		glGetShaderInfoLog (shader, 512, NULL, infoLog);
		std::string message = "Failed to compile shader source:\n";
		message += source;
		message += '\n';
		message += infoLog;
		throw std::runtime_error (message);
	}
	return shader;
}

GLuint _TEST_createShaderFromSourceFile (const char * filename, GLenum shaderType)
{
	std::ifstream file;
	file.open (filename);
	file.seekg (0, std::ios::end);
	size_t size = static_cast<size_t>( file.tellg ());
	std::string buffer (size, ' ');
	file.seekg (0);
	file.read (&buffer[0], size);
	return createShaderFromSource (buffer.data (), shaderType);
}

Camera camera;
double lastMouseY;
double lastMouseX;
constexpr double sensitivityX = 0.001f;
constexpr double sensitivityY = 0.001f;
constexpr float maxRoll = 80.0f;

static void cursor_pos_callback (GLFWwindow* window, double xpos, double ypos)
{
	double offsetX = xpos - lastMouseX;
	double offsetY = ypos - lastMouseY;
	lastMouseX = xpos;
	lastMouseY = ypos;
	int mouseState = glfwGetMouseButton (window, GLFW_MOUSE_BUTTON_LEFT);
	if (mouseState == GLFW_PRESS) {
		camera.yaw += static_cast<float>(offsetX * sensitivityX * 360.0);
	}
	else
	{
		camera.pitch += static_cast<float>(offsetX * sensitivityX * 360.0);
	}
	camera.roll = glm::clamp<float>(camera.roll + static_cast<float>(offsetY * sensitivityY * 360.0), -maxRoll, maxRoll);
	camera.calculate ();
}


void run ();


int main ()
{
	try 
	{
		run ();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what () << std::endl;
	}
	return 0;
}

void run () {
	glfwInit ();
	GLFWwindow *window = glfwCreateWindow (640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		throw std::runtime_error ("Failed to create window");
	}
	glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback (window, &cursor_pos_callback);

	glfwMakeContextCurrent (window);

	glfwSwapInterval (2);

	if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error ("Failed to load OpenGL");
	}
	camera.calculate ();

	GLuint vao;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);

	unsigned short vertcount, indcount;
	float * verts;
	unsigned short * inds;

	int c4dres = c4d2c ("../c4d/dummy", &vertcount, &verts, &indcount, &inds);
	if (c4dres)
	{
		std::cout << c4d2c_errstr (c4dres);
		return;
	}

	GLuint ebo;
	glGenBuffers (1, &ebo);
	GLuint vbo;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, vertcount * sizeof(float), verts, GL_STATIC_DRAW);
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, indcount * sizeof(unsigned short), inds, GL_STATIC_DRAW);

	GLuint vs = LOAD_SHADER ("default_vertex", GL_VERTEX_SHADER);
	GLuint fs = LOAD_SHADER ("default_fragment", GL_FRAGMENT_SHADER);
	GLuint shaderProgram = glCreateProgram ();
	glAttachShader (shaderProgram, vs);
	glAttachShader (shaderProgram, fs);
	glBindFragDataLocation (shaderProgram, 0, "outColor");
	glLinkProgram (shaderProgram);
	glUseProgram (shaderProgram);
	GLint posAttrib = glGetAttribLocation (shaderProgram, "aPosition");
	glVertexAttribPointer (posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) *6, (void*) (sizeof (float) * 0));
	glEnableVertexAttribArray (posAttrib);
	GLint normAttrib = glGetAttribLocation (shaderProgram, "aNormal");
	glVertexAttribPointer (normAttrib, 3, GL_FLOAT, GL_FALSE, sizeof (float) * 6, (void*) (sizeof(float) * 3));
	glEnableVertexAttribArray (normAttrib);
	GLint projviewUnif = glGetUniformLocation (shaderProgram, "uProjView");
	GLint lightposUnif = glGetUniformLocation (shaderProgram, "uLightPos");
	
	glDisable (GL_CULL_FACE);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);

	auto lastTime = std::chrono::high_resolution_clock::now ();
	while (window && !glfwWindowShouldClose (window))
	{
		auto currentTime = std::chrono::high_resolution_clock::now ();

		std::chrono::duration<float> deltaTime = currentTime - lastTime;
		glUniformMatrix4fv (projviewUnif, 1, GL_FALSE, camera.get ());
		glUniform3f (lightposUnif, 0.0f, 2.0f, 8.0f);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor (0, 0, 0, 1);
		glDrawElements (GL_TRIANGLES, indcount, GL_UNSIGNED_SHORT, 0);

		lastTime = currentTime;

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwDestroyWindow (window);
	glfwTerminate ();
}