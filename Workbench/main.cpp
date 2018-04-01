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
#include "C4D2C.h"

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

	int c4dres = c4d2c ("C:/Users/zocch/Desktop/prova.txt", &vertcount, &verts, &indcount, &inds);
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
	glVertexAttribPointer (posAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray (posAttrib);
	/*GLint colAttrib = glGetAttribLocation (shaderProgram, "aColor");
	glVertexAttribPointer (colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (colAttrib);
	GLint projviewUnif = glGetUniformLocation (shaderProgram, "uProjView");

	glDisable (GL_CULL_FACE);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);*/

	auto lastTime = std::chrono::high_resolution_clock::now ();
	while (window && !glfwWindowShouldClose (window))
	{
		auto currentTime = std::chrono::high_resolution_clock::now ();

		std::chrono::duration<float> deltaTime = currentTime - lastTime;
		//glUniformMatrix4fv (projviewUnif, 1, GL_FALSE, camera.get ());

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor (0, 0, 0, 1);
		glDrawElements (GL_TRIANGLES, indcount, GL_UNSIGNED_SHORT, 0);
		//glDrawArrays (GL_TRIANGLES, 0, 3);
		//glDrawArrays (GL_POINTS, 0, mesh.getVertexCount(1));
		//glDrawArrays (GL_LINES, 0, mesh.getVertexCount());



		lastTime = currentTime;

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwDestroyWindow (window);
	glfwTerminate ();
}