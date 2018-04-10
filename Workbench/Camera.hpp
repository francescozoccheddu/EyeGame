#pragma once
#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>

class Camera
{
public:

	int viewportWidth{ 1 };
	int viewportHeight{ 1 };
	float fov{ 90.0f };
	float nearPlane{ 1.0f };
	float farPlane{ 100.0f };

	glm::vec3 position{ 0.0f,0.0f,0.0f };

	void update ();

	void move (glm::vec3 direction);

	void turn (float angle);

	void lookUp (float angle);

	void tilt (float angle);

	glm::vec3 getUp ();

	glm::vec3 getForward ();

	glm::vec3 getRight ();

	const float *ptr ();

	void rotate (glm::vec3 axis, float angle);


private:

	glm::vec3 forward{ 0.0f,0.0f,1.0f };
	glm::vec3 up{ 0.0f,1.0f,0.0f };
	glm::mat4 combined;


};

