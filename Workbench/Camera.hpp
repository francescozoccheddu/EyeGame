#pragma once
#include <mat4x4.hpp>

class Camera
{
public:
	Camera ();
	virtual ~Camera ();

	void calculate ();

	const float* get ();

	int viewportWidth;
	int viewportHeight;
	float length;
	float fov;
	float roll;
	float pitch;
	float yaw;
	glm::vec3 target;

private:
	glm::mat4 combined;

	static float mouseModulo (double value, double sensitivity);

};

