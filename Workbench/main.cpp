#include <stdexcept>
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Camera.hpp"

#define LOAD_SHADER(name, type) _TEST_createShaderFromSourceFile(R"(C:\Users\zocch\OneDrive\Projects\EyeGame\EyeGame\Workbench\)" name ".glsl", type)

GLuint createShaderFromSource (const char * source, GLenum shaderType)
{
	GLuint shader = glCreateShader (shaderType);
	if (shader == 0)
	{
		throw std::runtime_error ("Filed to create shader");
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
		std::cout << "boh";
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


	float vertices[] = {
		0.0,-1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,0.0,0.258819045103,-0.965925826289,0.0,0.258819045103,0.965925826289,0.0,0.25,-0.965925826289,0.0669872981078,0.25,0.965925826289,0.0669872981078,0.224143868042,-0.965925826289,0.129409522551,0.224143868042,0.965925826289,0.129409522551,0.183012701892,-0.965925826289,0.183012701892,0.183012701892,0.965925826289,0.183012701892,0.129409522551,-0.965925826289,0.224143868042,0.129409522551,0.965925826289,0.224143868042,0.0669872981078,-0.965925826289,0.25,0.0669872981078,0.965925826289,0.25,1.58480957572e-17,-0.965925826289,0.258819045103,1.58480957572e-17,0.965925826289,0.258819045103,-0.0669872981078,-0.965925826289,0.25,0.0669872981078,0.965925826289,0.25,-0.129409522551,-0.965925826289,0.224143868042,0.129409522551,0.965925826289,0.224143868042,-0.183012701892,-0.965925826289,0.183012701892,0.183012701892,0.965925826289,0.183012701892,-0.224143868042,-0.965925826289,0.129409522551,0.224143868042,0.965925826289,0.129409522551,-0.25,-0.965925826289,0.0669872981078,0.25,0.965925826289,0.0669872981078,-0.258819045103,-0.965925826289,3.16961915143e-17,0.258819045103,0.965925826289,3.16961915143e-17,-0.25,-0.965925826289,-0.0669872981078,0.25,0.965925826289,0.0669872981078,-0.224143868042,-0.965925826289,-0.129409522551,0.224143868042,0.965925826289,0.129409522551,-0.183012701892,-0.965925826289,-0.183012701892,0.183012701892,0.965925826289,0.183012701892,-0.129409522551,-0.965925826289,-0.224143868042,0.129409522551,0.965925826289,0.224143868042,-0.0669872981078,-0.965925826289,-0.25,0.0669872981078,0.965925826289,0.25,-4.75442872715e-17,-0.965925826289,-0.258819045103,4.75442872715e-17,0.965925826289,0.258819045103,0.0669872981078,-0.965925826289,-0.25,0.0669872981078,0.965925826289,0.25,0.129409522551,-0.965925826289,-0.224143868042,0.129409522551,0.965925826289,0.224143868042,0.183012701892,-0.965925826289,-0.183012701892,0.183012701892,0.965925826289,0.183012701892,0.224143868042,-0.965925826289,-0.129409522551,0.224143868042,0.965925826289,0.129409522551,0.25,-0.965925826289,-0.0669872981078,0.25,0.965925826289,0.0669872981078,0.5,-0.866025403784,0.0,0.5,0.866025403784,0.0,0.482962913145,-0.866025403784,0.129409522551,0.482962913145,0.866025403784,0.129409522551,0.433012701892,-0.866025403784,0.25,0.433012701892,0.866025403784,0.25,0.353553390593,-0.866025403784,0.353553390593,0.353553390593,0.866025403784,0.353553390593,0.25,-0.866025403784,0.433012701892,0.25,0.866025403784,0.433012701892,0.129409522551,-0.866025403784,0.482962913145,0.129409522551,0.866025403784,0.482962913145,3.06161699787e-17,-0.866025403784,0.5,3.06161699787e-17,0.866025403784,0.5,-0.129409522551,-0.866025403784,0.482962913145,0.129409522551,0.866025403784,0.482962913145,-0.25,-0.866025403784,0.433012701892,0.25,0.866025403784,0.433012701892,-0.353553390593,-0.866025403784,0.353553390593,0.353553390593,0.866025403784,0.353553390593,-0.433012701892,-0.866025403784,0.25,0.433012701892,0.866025403784,0.25,-0.482962913145,-0.866025403784,0.129409522551,0.482962913145,0.866025403784,0.129409522551,-0.5,-0.866025403784,6.12323399574e-17,0.5,0.866025403784,6.12323399574e-17,-0.482962913145,-0.866025403784,-0.129409522551,0.482962913145,0.866025403784,0.129409522551,-0.433012701892,-0.866025403784,-0.25,0.433012701892,0.866025403784,0.25,-0.353553390593,-0.866025403784,-0.353553390593,0.353553390593,0.866025403784,0.353553390593,-0.25,-0.866025403784,-0.433012701892,0.25,0.866025403784,0.433012701892,-0.129409522551,-0.866025403784,-0.482962913145,0.129409522551,0.866025403784,0.482962913145,-9.18485099361e-17,-0.866025403784,-0.5,9.18485099361e-17,0.866025403784,0.5,0.129409522551,-0.866025403784,-0.482962913145,0.129409522551,0.866025403784,0.482962913145,0.25,-0.866025403784,-0.433012701892,0.25,0.866025403784,0.433012701892,0.353553390593,-0.866025403784,-0.353553390593,0.353553390593,0.866025403784,0.353553390593,0.433012701892,-0.866025403784,-0.25,0.433012701892,0.866025403784,0.25,0.482962913145,-0.866025403784,-0.129409522551,0.482962913145,0.866025403784,0.129409522551,0.707106781187,-0.707106781187,0.0,0.707106781187,0.707106781187,0.0,0.683012701892,-0.707106781187,0.183012701892,0.683012701892,0.707106781187,0.183012701892,0.612372435696,-0.707106781187,0.353553390593,0.612372435696,0.707106781187,0.353553390593,0.5,-0.707106781187,0.5,0.5,0.707106781187,0.5,0.353553390593,-0.707106781187,0.612372435696,0.353553390593,0.707106781187,0.612372435696,0.183012701892,-0.707106781187,0.683012701892,0.183012701892,0.707106781187,0.683012701892,4.32978028118e-17,-0.707106781187,0.707106781187,4.32978028118e-17,0.707106781187,0.707106781187,-0.183012701892,-0.707106781187,0.683012701892,0.183012701892,0.707106781187,0.683012701892,-0.353553390593,-0.707106781187,0.612372435696,0.353553390593,0.707106781187,0.612372435696,-0.5,-0.707106781187,0.5,0.5,0.707106781187,0.5,-0.612372435696,-0.707106781187,0.353553390593,0.612372435696,0.707106781187,0.353553390593,-0.683012701892,-0.707106781187,0.183012701892,0.683012701892,0.707106781187,0.183012701892,-0.707106781187,-0.707106781187,8.65956056235e-17,0.707106781187,0.707106781187,8.65956056235e-17,-0.683012701892,-0.707106781187,-0.183012701892,0.683012701892,0.707106781187,0.183012701892,-0.612372435696,-0.707106781187,-0.353553390593,0.612372435696,0.707106781187,0.353553390593,-0.5,-0.707106781187,-0.5,0.5,0.707106781187,0.5,-0.353553390593,-0.707106781187,-0.612372435696,0.353553390593,0.707106781187,0.612372435696,-0.183012701892,-0.707106781187,-0.683012701892,0.183012701892,0.707106781187,0.683012701892,-1.29893408435e-16,-0.707106781187,-0.707106781187,1.29893408435e-16,0.707106781187,0.707106781187,0.183012701892,-0.707106781187,-0.683012701892,0.183012701892,0.707106781187,0.683012701892,0.353553390593,-0.707106781187,-0.612372435696,0.353553390593,0.707106781187,0.612372435696,0.5,-0.707106781187,-0.5,0.5,0.707106781187,0.5,0.612372435696,-0.707106781187,-0.353553390593,0.612372435696,0.707106781187,0.353553390593,0.683012701892,-0.707106781187,-0.183012701892,0.683012701892,0.707106781187,0.183012701892,0.866025403784,-0.5,0.0,0.866025403784,0.5,0.0,0.836516303738,-0.5,0.224143868042,0.836516303738,0.5,0.224143868042,0.75,-0.5,0.433012701892,0.75,0.5,0.433012701892,0.612372435696,-0.5,0.612372435696,0.612372435696,0.5,0.612372435696,0.433012701892,-0.5,0.75,0.433012701892,0.5,0.75,0.224143868042,-0.5,0.836516303738,0.224143868042,0.5,0.836516303738,5.30287619362e-17,-0.5,0.866025403784,5.30287619362e-17,0.5,0.866025403784,-0.224143868042,-0.5,0.836516303738,0.224143868042,0.5,0.836516303738,-0.433012701892,-0.5,0.75,0.433012701892,0.5,0.75,-0.612372435696,-0.5,0.612372435696,0.612372435696,0.5,0.612372435696,-0.75,-0.5,0.433012701892,0.75,0.5,0.433012701892,-0.836516303738,-0.5,0.224143868042,0.836516303738,0.5,0.224143868042,-0.866025403784,-0.5,1.06057523872e-16,0.866025403784,0.5,1.06057523872e-16,-0.836516303738,-0.5,-0.224143868042,0.836516303738,0.5,0.224143868042,-0.75,-0.5,-0.433012701892,0.75,0.5,0.433012701892,-0.612372435696,-0.5,-0.612372435696,0.612372435696,0.5,0.612372435696,-0.433012701892,-0.5,-0.75,0.433012701892,0.5,0.75,-0.224143868042,-0.5,-0.836516303738,0.224143868042,0.5,0.836516303738,-1.59086285809e-16,-0.5,-0.866025403784,1.59086285809e-16,0.5,0.866025403784,0.224143868042,-0.5,-0.836516303738,0.224143868042,0.5,0.836516303738,0.433012701892,-0.5,-0.75,0.433012701892,0.5,0.75,0.612372435696,-0.5,-0.612372435696,0.612372435696,0.5,0.612372435696,0.75,-0.5,-0.433012701892,0.75,0.5,0.433012701892,0.836516303738,-0.5,-0.224143868042,0.836516303738,0.5,0.224143868042,0.965925826289,-0.258819045103,0.0,0.965925826289,0.258819045103,0.0,0.933012701892,-0.258819045103,0.25,0.933012701892,0.258819045103,0.25,0.836516303738,-0.258819045103,0.482962913145,0.836516303738,0.258819045103,0.482962913145,0.683012701892,-0.258819045103,0.683012701892,0.683012701892,0.258819045103,0.683012701892,0.482962913145,-0.258819045103,0.836516303738,0.482962913145,0.258819045103,0.836516303738,0.25,-0.258819045103,0.933012701892,0.25,0.258819045103,0.933012701892,5.91458985689e-17,-0.258819045103,0.965925826289,5.91458985689e-17,0.258819045103,0.965925826289,-0.25,-0.258819045103,0.933012701892,0.25,0.258819045103,0.933012701892,-0.482962913145,-0.258819045103,0.836516303738,0.482962913145,0.258819045103,0.836516303738,-0.683012701892,-0.258819045103,0.683012701892,0.683012701892,0.258819045103,0.683012701892,-0.836516303738,-0.258819045103,0.482962913145,0.836516303738,0.258819045103,0.482962913145,-0.933012701892,-0.258819045103,0.25,0.933012701892,0.258819045103,0.25,-0.965925826289,-0.258819045103,1.18291797138e-16,0.965925826289,0.258819045103,1.18291797138e-16,-0.933012701892,-0.258819045103,-0.25,0.933012701892,0.258819045103,0.25,-0.836516303738,-0.258819045103,-0.482962913145,0.836516303738,0.258819045103,0.482962913145,-0.683012701892,-0.258819045103,-0.683012701892,0.683012701892,0.258819045103,0.683012701892,-0.482962913145,-0.258819045103,-0.836516303738,0.482962913145,0.258819045103,0.836516303738,-0.25,-0.258819045103,-0.933012701892,0.25,0.258819045103,0.933012701892,-1.77437695707e-16,-0.258819045103,-0.965925826289,1.77437695707e-16,0.258819045103,0.965925826289,0.25,-0.258819045103,-0.933012701892,0.25,0.258819045103,0.933012701892,0.482962913145,-0.258819045103,-0.836516303738,0.482962913145,0.258819045103,0.836516303738,0.683012701892,-0.258819045103,-0.683012701892,0.683012701892,0.258819045103,0.683012701892,0.836516303738,-0.258819045103,-0.482962913145,0.836516303738,0.258819045103,0.482962913145,0.933012701892,-0.258819045103,-0.25,0.933012701892,0.258819045103,0.25,1.0,0.0,0.0,1.0,0.0,0.0,0.965925826289,0.0,0.258819045103,0.965925826289,0.0,0.258819045103,0.866025403784,0.0,0.5,0.866025403784,0.0,0.5,0.707106781187,0.0,0.707106781187,0.707106781187,0.0,0.707106781187,0.5,0.0,0.866025403784,0.5,0.0,0.866025403784,0.258819045103,0.0,0.965925826289,0.258819045103,0.0,0.965925826289,6.12323399574e-17,0.0,1.0,6.12323399574e-17,0.0,1.0,-0.258819045103,0.0,0.965925826289,0.258819045103,0.0,0.965925826289,-0.5,0.0,0.866025403784,0.5,0.0,0.866025403784,-0.707106781187,0.0,0.707106781187,0.707106781187,0.0,0.707106781187,-0.866025403784,0.0,0.5,0.866025403784,0.0,0.5,-0.965925826289,0.0,0.258819045103,0.965925826289,0.0,0.258819045103,-1.0,0.0,1.22464679915e-16,1.0,0.0,1.22464679915e-16,-0.965925826289,0.0,-0.258819045103,0.965925826289,0.0,0.258819045103,-0.866025403784,0.0,-0.5,0.866025403784,0.0,0.5,-0.707106781187,0.0,-0.707106781187,0.707106781187,0.0,0.707106781187,-0.5,0.0,-0.866025403784,0.5,0.0,0.866025403784,-0.258819045103,0.0,-0.965925826289,0.258819045103,0.0,0.965925826289,-1.83697019872e-16,0.0,-1.0,1.83697019872e-16,0.0,1.0,0.258819045103,0.0,-0.965925826289,0.258819045103,0.0,0.965925826289,0.5,0.0,-0.866025403784,0.5,0.0,0.866025403784,0.707106781187,0.0,-0.707106781187,0.707106781187,0.0,0.707106781187,0.866025403784,0.0,-0.5,0.866025403784,0.0,0.5,0.965925826289,0.0,-0.258819045103,0.965925826289,0.0,0.258819045103,0.965925826289,0.258819045103,0.0,0.965925826289,0.258819045103,0.0,0.933012701892,0.258819045103,0.25,0.933012701892,0.258819045103,0.25,0.836516303738,0.258819045103,0.482962913145,0.836516303738,0.258819045103,0.482962913145,0.683012701892,0.258819045103,0.683012701892,0.683012701892,0.258819045103,0.683012701892,0.482962913145,0.258819045103,0.836516303738,0.482962913145,0.258819045103,0.836516303738,0.25,0.258819045103,0.933012701892,0.25,0.258819045103,0.933012701892,5.91458985689e-17,0.258819045103,0.965925826289,5.91458985689e-17,0.258819045103,0.965925826289,-0.25,0.258819045103,0.933012701892,0.25,0.258819045103,0.933012701892,-0.482962913145,0.258819045103,0.836516303738,0.482962913145,0.258819045103,0.836516303738,-0.683012701892,0.258819045103,0.683012701892,0.683012701892,0.258819045103,0.683012701892,-0.836516303738,0.258819045103,0.482962913145,0.836516303738,0.258819045103,0.482962913145,-0.933012701892,0.258819045103,0.25,0.933012701892,0.258819045103,0.25,-0.965925826289,0.258819045103,1.18291797138e-16,0.965925826289,0.258819045103,1.18291797138e-16,-0.933012701892,0.258819045103,-0.25,0.933012701892,0.258819045103,0.25,-0.836516303738,0.258819045103,-0.482962913145,0.836516303738,0.258819045103,0.482962913145,-0.683012701892,0.258819045103,-0.683012701892,0.683012701892,0.258819045103,0.683012701892,-0.482962913145,0.258819045103,-0.836516303738,0.482962913145,0.258819045103,0.836516303738,-0.25,0.258819045103,-0.933012701892,0.25,0.258819045103,0.933012701892,-1.77437695707e-16,0.258819045103,-0.965925826289,1.77437695707e-16,0.258819045103,0.965925826289,0.25,0.258819045103,-0.933012701892,0.25,0.258819045103,0.933012701892,0.482962913145,0.258819045103,-0.836516303738,0.482962913145,0.258819045103,0.836516303738,0.683012701892,0.258819045103,-0.683012701892,0.683012701892,0.258819045103,0.683012701892,0.836516303738,0.258819045103,-0.482962913145,0.836516303738,0.258819045103,0.482962913145,0.933012701892,0.258819045103,-0.25,0.933012701892,0.258819045103,0.25,0.866025403784,0.5,0.0,0.866025403784,0.5,0.0,0.836516303738,0.5,0.224143868042,0.836516303738,0.5,0.224143868042,0.75,0.5,0.433012701892,0.75,0.5,0.433012701892,0.612372435696,0.5,0.612372435696,0.612372435696,0.5,0.612372435696,0.433012701892,0.5,0.75,0.433012701892,0.5,0.75,0.224143868042,0.5,0.836516303738,0.224143868042,0.5,0.836516303738,5.30287619362e-17,0.5,0.866025403784,5.30287619362e-17,0.5,0.866025403784,-0.224143868042,0.5,0.836516303738,0.224143868042,0.5,0.836516303738,-0.433012701892,0.5,0.75,0.433012701892,0.5,0.75,-0.612372435696,0.5,0.612372435696,0.612372435696,0.5,0.612372435696,-0.75,0.5,0.433012701892,0.75,0.5,0.433012701892,-0.836516303738,0.5,0.224143868042,0.836516303738,0.5,0.224143868042,-0.866025403784,0.5,1.06057523872e-16,0.866025403784,0.5,1.06057523872e-16,-0.836516303738,0.5,-0.224143868042,0.836516303738,0.5,0.224143868042,-0.75,0.5,-0.433012701892,0.75,0.5,0.433012701892,-0.612372435696,0.5,-0.612372435696,0.612372435696,0.5,0.612372435696,-0.433012701892,0.5,-0.75,0.433012701892,0.5,0.75,-0.224143868042,0.5,-0.836516303738,0.224143868042,0.5,0.836516303738,-1.59086285809e-16,0.5,-0.866025403784,1.59086285809e-16,0.5,0.866025403784,0.224143868042,0.5,-0.836516303738,0.224143868042,0.5,0.836516303738,0.433012701892,0.5,-0.75,0.433012701892,0.5,0.75,0.612372435696,0.5,-0.612372435696,0.612372435696,0.5,0.612372435696,0.75,0.5,-0.433012701892,0.75,0.5,0.433012701892,0.836516303738,0.5,-0.224143868042,0.836516303738,0.5,0.224143868042,0.707106781187,0.707106781187,0.0,0.707106781187,0.707106781187,0.0,0.683012701892,0.707106781187,0.183012701892,0.683012701892,0.707106781187,0.183012701892,0.612372435696,0.707106781187,0.353553390593,0.612372435696,0.707106781187,0.353553390593,0.5,0.707106781187,0.5,0.5,0.707106781187,0.5,0.353553390593,0.707106781187,0.612372435696,0.353553390593,0.707106781187,0.612372435696,0.183012701892,0.707106781187,0.683012701892,0.183012701892,0.707106781187,0.683012701892,4.32978028118e-17,0.707106781187,0.707106781187,4.32978028118e-17,0.707106781187,0.707106781187,-0.183012701892,0.707106781187,0.683012701892,0.183012701892,0.707106781187,0.683012701892,-0.353553390593,0.707106781187,0.612372435696,0.353553390593,0.707106781187,0.612372435696,-0.5,0.707106781187,0.5,0.5,0.707106781187,0.5,-0.612372435696,0.707106781187,0.353553390593,0.612372435696,0.707106781187,0.353553390593,-0.683012701892,0.707106781187,0.183012701892,0.683012701892,0.707106781187,0.183012701892,-0.707106781187,0.707106781187,8.65956056235e-17,0.707106781187,0.707106781187,8.65956056235e-17,-0.683012701892,0.707106781187,-0.183012701892,0.683012701892,0.707106781187,0.183012701892,-0.612372435696,0.707106781187,-0.353553390593,0.612372435696,0.707106781187,0.353553390593,-0.5,0.707106781187,-0.5,0.5,0.707106781187,0.5,-0.353553390593,0.707106781187,-0.612372435696,0.353553390593,0.707106781187,0.612372435696,-0.183012701892,0.707106781187,-0.683012701892,0.183012701892,0.707106781187,0.683012701892,-1.29893408435e-16,0.707106781187,-0.707106781187,1.29893408435e-16,0.707106781187,0.707106781187,0.183012701892,0.707106781187,-0.683012701892,0.183012701892,0.707106781187,0.683012701892,0.353553390593,0.707106781187,-0.612372435696,0.353553390593,0.707106781187,0.612372435696,0.5,0.707106781187,-0.5,0.5,0.707106781187,0.5,0.612372435696,0.707106781187,-0.353553390593,0.612372435696,0.707106781187,0.353553390593,0.683012701892,0.707106781187,-0.183012701892,0.683012701892,0.707106781187,0.183012701892,0.5,0.866025403784,0.0,0.5,0.866025403784,0.0,0.482962913145,0.866025403784,0.129409522551,0.482962913145,0.866025403784,0.129409522551,0.433012701892,0.866025403784,0.25,0.433012701892,0.866025403784,0.25,0.353553390593,0.866025403784,0.353553390593,0.353553390593,0.866025403784,0.353553390593,0.25,0.866025403784,0.433012701892,0.25,0.866025403784,0.433012701892,0.129409522551,0.866025403784,0.482962913145,0.129409522551,0.866025403784,0.482962913145,3.06161699787e-17,0.866025403784,0.5,3.06161699787e-17,0.866025403784,0.5,-0.129409522551,0.866025403784,0.482962913145,0.129409522551,0.866025403784,0.482962913145,-0.25,0.866025403784,0.433012701892,0.25,0.866025403784,0.433012701892,-0.353553390593,0.866025403784,0.353553390593,0.353553390593,0.866025403784,0.353553390593,-0.433012701892,0.866025403784,0.25,0.433012701892,0.866025403784,0.25,-0.482962913145,0.866025403784,0.129409522551,0.482962913145,0.866025403784,0.129409522551,-0.5,0.866025403784,6.12323399574e-17,0.5,0.866025403784,6.12323399574e-17,-0.482962913145,0.866025403784,-0.129409522551,0.482962913145,0.866025403784,0.129409522551,-0.433012701892,0.866025403784,-0.25,0.433012701892,0.866025403784,0.25,-0.353553390593,0.866025403784,-0.353553390593,0.353553390593,0.866025403784,0.353553390593,-0.25,0.866025403784,-0.433012701892,0.25,0.866025403784,0.433012701892,-0.129409522551,0.866025403784,-0.482962913145,0.129409522551,0.866025403784,0.482962913145,-9.18485099361e-17,0.866025403784,-0.5,9.18485099361e-17,0.866025403784,0.5,0.129409522551,0.866025403784,-0.482962913145,0.129409522551,0.866025403784,0.482962913145,0.25,0.866025403784,-0.433012701892,0.25,0.866025403784,0.433012701892,0.353553390593,0.866025403784,-0.353553390593,0.353553390593,0.866025403784,0.353553390593,0.433012701892,0.866025403784,-0.25,0.433012701892,0.866025403784,0.25,0.482962913145,0.866025403784,-0.129409522551,0.482962913145,0.866025403784,0.129409522551,0.258819045103,0.965925826289,0.0,0.258819045103,0.965925826289,0.0,0.25,0.965925826289,0.0669872981078,0.25,0.965925826289,0.0669872981078,0.224143868042,0.965925826289,0.129409522551,0.224143868042,0.965925826289,0.129409522551,0.183012701892,0.965925826289,0.183012701892,0.183012701892,0.965925826289,0.183012701892,0.129409522551,0.965925826289,0.224143868042,0.129409522551,0.965925826289,0.224143868042,0.0669872981078,0.965925826289,0.25,0.0669872981078,0.965925826289,0.25,1.58480957572e-17,0.965925826289,0.258819045103,1.58480957572e-17,0.965925826289,0.258819045103,-0.0669872981078,0.965925826289,0.25,0.0669872981078,0.965925826289,0.25,-0.129409522551,0.965925826289,0.224143868042,0.129409522551,0.965925826289,0.224143868042,-0.183012701892,0.965925826289,0.183012701892,0.183012701892,0.965925826289,0.183012701892,-0.224143868042,0.965925826289,0.129409522551,0.224143868042,0.965925826289,0.129409522551,-0.25,0.965925826289,0.0669872981078,0.25,0.965925826289,0.0669872981078,-0.258819045103,0.965925826289,3.16961915143e-17,0.258819045103,0.965925826289,3.16961915143e-17,-0.25,0.965925826289,-0.0669872981078,0.25,0.965925826289,0.0669872981078,-0.224143868042,0.965925826289,-0.129409522551,0.224143868042,0.965925826289,0.129409522551,-0.183012701892,0.965925826289,-0.183012701892,0.183012701892,0.965925826289,0.183012701892,-0.129409522551,0.965925826289,-0.224143868042,0.129409522551,0.965925826289,0.224143868042,-0.0669872981078,0.965925826289,-0.25,0.0669872981078,0.965925826289,0.25,-4.75442872715e-17,0.965925826289,-0.258819045103,4.75442872715e-17,0.965925826289,0.258819045103,0.0669872981078,0.965925826289,-0.25,0.0669872981078,0.965925826289,0.25,0.129409522551,0.965925826289,-0.224143868042,0.129409522551,0.965925826289,0.224143868042,0.183012701892,0.965925826289,-0.183012701892,0.183012701892,0.965925826289,0.183012701892,0.224143868042,0.965925826289,-0.129409522551,0.224143868042,0.965925826289,0.129409522551,0.25,0.965925826289,-0.0669872981078,0.25,0.965925826289,0.0669872981078,
	};

	GLuint indices[] = {
		1,25,26,2,26,27,3,27,28,4,28,29,5,29,30,6,30,31,7,31,32,8,32,33,9,33,34,10,34,35,11,35,36,12,36,37,13,37,38,14,38,39,15,39,40,16,40,41,17,41,42,18,42,43,19,43,44,20,44,45,21,45,46,22,46,47,23,47,48,24,48,25,25,49,50,26,50,51,27,51,52,28,52,53,29,53,54,30,54,55,31,55,56,32,56,57,33,57,58,34,58,59,35,59,60,36,60,61,37,61,62,38,62,63,39,63,64,40,64,65,41,65,66,42,66,67,43,67,68,44,68,69,45,69,70,46,70,71,47,71,72,48,72,49,49,73,74,50,74,75,51,75,76,52,76,77,53,77,78,54,78,79,55,79,80,56,80,81,57,81,82,58,82,83,59,83,84,60,84,85,61,85,86,62,86,87,63,87,88,64,88,89,65,89,90,66,90,91,67,91,92,68,92,93,69,93,94,70,94,95,71,95,96,72,96,73,73,97,98,74,98,99,75,99,100,76,100,101,77,101,102,78,102,103,79,103,104,80,104,105,81,105,106,82,106,107,83,107,108,84,108,109,85,109,110,86,110,111,87,111,112,88,112,113,89,113,114,90,114,115,91,115,116,92,116,117,93,117,118,94,118,119,95,119,120,96,120,97,97,121,122,98,122,123,99,123,124,100,124,125,101,125,126,102,126,127,103,127,128,104,128,129,105,129,130,106,130,131,107,131,132,108,132,133,109,133,134,110,134,135,111,135,136,112,136,137,113,137,138,114,138,139,115,139,140,116,140,141,117,141,142,118,142,143,119,143,144,120,144,121,121,145,146,122,146,147,123,147,148,124,148,149,125,149,150,126,150,151,127,151,152,128,152,153,129,153,154,130,154,155,131,155,156,132,156,157,133,157,158,134,158,159,135,159,160,136,160,161,137,161,162,138,162,163,139,163,164,140,164,165,141,165,166,142,166,167,143,167,168,144,168,145,145,169,170,146,170,171,147,171,172,148,172,173,149,173,174,150,174,175,151,175,176,152,176,177,153,177,178,154,178,179,155,179,180,156,180,181,157,181,182,158,182,183,159,183,184,160,184,185,161,185,186,162,186,187,163,187,188,164,188,189,165,189,190,166,190,191,167,191,192,168,192,169,169,193,194,170,194,195,171,195,196,172,196,197,173,197,198,174,198,199,175,199,200,176,200,201,177,201,202,178,202,203,179,203,204,180,204,205,181,205,206,182,206,207,183,207,208,184,208,209,185,209,210,186,210,211,187,211,212,188,212,213,189,213,214,190,214,215,191,215,216,192,216,193,193,217,218,194,218,219,195,219,220,196,220,221,197,221,222,198,222,223,199,223,224,200,224,225,201,225,226,202,226,227,203,227,228,204,228,229,205,229,230,206,230,231,207,231,232,208,232,233,209,233,234,210,234,235,211,235,236,212,236,237,213,237,238,214,238,239,215,239,240,216,240,217,217,241,242,218,242,243,219,243,244,220,244,245,221,245,246,222,246,247,223,247,248,224,248,249,225,249,250,226,250,251,227,251,252,228,252,253,229,253,254,230,254,255,231,255,256,232,256,257,233,257,258,234,258,259,235,259,260,236,260,261,237,261,262,238,262,263,239,263,264,240,264,241,-1,1,2,242,241,0,-1,2,3,243,242,0,-1,3,4,244,243,0,-1,4,5,245,244,0,-1,5,6,246,245,0,-1,6,7,247,246,0,-1,7,8,248,247,0,-1,8,9,249,248,0,-1,9,10,250,249,0,-1,10,11,251,250,0,-1,11,12,252,251,0,-1,12,13,253,252,0,-1,13,14,254,253,0,-1,14,15,255,254,0,-1,15,16,256,255,0,-1,16,17,257,256,0,-1,17,18,258,257,0,-1,18,19,259,258,0,-1,19,20,260,259,0,-1,20,21,261,260,0,-1,21,22,262,261,0,-1,22,23,263,262,0,-1,23,24,264,263,0,-1,24,1,241,264,0,1,26,2,2,27,3,3,28,4,4,29,5,5,30,6,6,31,7,7,32,8,8,33,9,9,34,10,10,35,11,11,36,12,12,37,13,13,38,14,14,39,15,15,40,16,16,41,17,17,42,18,18,43,19,19,44,20,20,45,21,21,46,22,22,47,23,23,48,24,24,25,1,25,50,26,26,51,27,27,52,28,28,53,29,29,54,30,30,55,31,31,56,32,32,57,33,33,58,34,34,59,35,35,60,36,36,61,37,37,62,38,38,63,39,39,64,40,40,65,41,41,66,42,42,67,43,43,68,44,44,69,45,45,70,46,46,71,47,47,72,48,48,49,25,49,74,50,50,75,51,51,76,52,52,77,53,53,78,54,54,79,55,55,80,56,56,81,57,57,82,58,58,83,59,59,84,60,60,85,61,61,86,62,62,87,63,63,88,64,64,89,65,65,90,66,66,91,67,67,92,68,68,93,69,69,94,70,70,95,71,71,96,72,72,73,49,73,98,74,74,99,75,75,100,76,76,101,77,77,102,78,78,103,79,79,104,80,80,105,81,81,106,82,82,107,83,83,108,84,84,109,85,85,110,86,86,111,87,87,112,88,88,113,89,89,114,90,90,115,91,91,116,92,92,117,93,93,118,94,94,119,95,95,120,96,96,97,73,97,122,98,98,123,99,99,124,100,100,125,101,101,126,102,102,127,103,103,128,104,104,129,105,105,130,106,106,131,107,107,132,108,108,133,109,109,134,110,110,135,111,111,136,112,112,137,113,113,138,114,114,139,115,115,140,116,116,141,117,117,142,118,118,143,119,119,144,120,120,121,97,121,146,122,122,147,123,123,148,124,124,149,125,125,150,126,126,151,127,127,152,128,128,153,129,129,154,130,130,155,131,131,156,132,132,157,133,133,158,134,134,159,135,135,160,136,136,161,137,137,162,138,138,163,139,139,164,140,140,165,141,141,166,142,142,167,143,143,168,144,144,145,121,145,170,146,146,171,147,147,172,148,148,173,149,149,174,150,150,175,151,151,176,152,152,177,153,153,178,154,154,179,155,155,180,156,156,181,157,157,182,158,158,183,159,159,184,160,160,185,161,161,186,162,162,187,163,163,188,164,164,189,165,165,190,166,166,191,167,167,192,168,168,169,145,169,194,170,170,195,171,171,196,172,172,197,173,173,198,174,174,199,175,175,200,176,176,201,177,177,202,178,178,203,179,179,204,180,180,205,181,181,206,182,182,207,183,183,208,184,184,209,185,185,210,186,186,211,187,187,212,188,188,213,189,189,214,190,190,215,191,191,216,192,192,193,169,193,218,194,194,219,195,195,220,196,196,221,197,197,222,198,198,223,199,199,224,200,200,225,201,201,226,202,202,227,203,203,228,204,204,229,205,205,230,206,206,231,207,207,232,208,208,233,209,209,234,210,210,235,211,211,236,212,212,237,213,213,238,214,214,239,215,215,240,216,216,217,193,217,242,218,218,243,219,219,244,220,220,245,221,221,246,222,222,247,223,223,248,224,224,249,225,225,250,226,226,251,227,227,252,228,228,253,229,229,254,230,230,255,231,231,256,232,232,257,233,233,258,234,234,259,235,235,260,236,236,261,237,237,262,238,238,263,239,239,264,240,240,241,217,
	};
	GLuint vao;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	GLuint ebo;
	glGenBuffers (1, &ebo);
	GLuint vbo;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData (GL_ELEMENT_ARRAY_BUFFER,
		sizeof (indices), indices, GL_STATIC_DRAW);
	GLuint vs = LOAD_SHADER ("default_vertex", GL_VERTEX_SHADER);
	GLuint fs = LOAD_SHADER ("default_fragment", GL_FRAGMENT_SHADER);
	GLuint shaderProgram = glCreateProgram ();
	glAttachShader (shaderProgram, vs);
	glAttachShader (shaderProgram, fs);
	glBindFragDataLocation (shaderProgram, 0, "outColor");
	glLinkProgram (shaderProgram);
	glUseProgram (shaderProgram);
	GLint posAttrib = glGetAttribLocation (shaderProgram, "aPosition");
	glVertexAttribPointer (posAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	glEnableVertexAttribArray (posAttrib);
	GLint colAttrib = glGetAttribLocation (shaderProgram, "aColor");
	glVertexAttribPointer (colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray (colAttrib);
	GLint projviewUnif = glGetUniformLocation (shaderProgram, "uProjView");

	glDisable (GL_CULL_FACE);
	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);


	auto lastTime = std::chrono::high_resolution_clock::now ();
	while (window && !glfwWindowShouldClose (window))
	{
		auto currentTime = std::chrono::high_resolution_clock::now ();

		std::chrono::duration<float> deltaTime = currentTime - lastTime;
		glUniformMatrix4fv (projviewUnif, 1, GL_FALSE, camera.get ());

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor (0, 0, 0, 1);
		glDrawElements (GL_TRIANGLES, sizeof(indices)/(sizeof(GLuint)), GL_UNSIGNED_INT, 0);

		lastTime = currentTime;

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwDestroyWindow (window);
	glfwTerminate ();
}