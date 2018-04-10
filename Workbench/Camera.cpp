#include "Camera.hpp"
#include <glm.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/type_ptr.hpp>

void Camera::update ()
{
	float aspectRatio = viewportWidth / static_cast<float>(viewportHeight);
	glm::mat4 projection = glm::perspective (glm::radians(fov), aspectRatio, nearPlane, farPlane);
	glm::mat4 view = glm::lookAt (position, position + forward, up);
	combined = projection * view;
}

void Camera::move (glm::vec3 direction)
{
	position += direction.x * getRight ();
	position += direction.y * getUp ();
	position += direction.z * getForward ();
}

void Camera::turn (float angle)
{
	rotate (getUp(), angle);
}

void Camera::lookUp (float angle)
{
	rotate (getRight (), angle);
}

void Camera::tilt (float angle)
{
	rotate(getForward(),angle);
}

glm::vec3 Camera::getUp ()
{
	return up;
}

glm::vec3 Camera::getForward ()
{
	return forward;
}

glm::vec3 Camera::getRight ()
{
	glm::vec3 cross = glm::cross (forward, up);
	return cross;
}

const float * Camera::ptr ()
{
	return glm::value_ptr (combined);
}

void Camera::rotate (glm::vec3 axis, float angle)
{
	glm::quat rot{};
	rot = glm::rotate (rot, angle, axis);
	forward = rot * forward;
	up = rot * up;
}