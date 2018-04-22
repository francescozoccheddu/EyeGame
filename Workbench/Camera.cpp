#include "Camera.hpp"
#include <glm.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/type_ptr.hpp>


Camera::Camera (glm::vec3 _forward, glm::vec3 _up) : unr_forward{ _forward }, unr_up{ _up }
{}

void Camera::update ()
{
	float aspectRatio = viewportWidth / static_cast<float>(viewportHeight);
	glm::mat4 projection = glm::perspective (glm::radians (fov), aspectRatio, nearPlane, farPlane);
	glm::quat rot{ glm::vec3{lookUpAngle, turnAngle, tiltAngle } };
	glm::mat4 view = glm::lookAt (position, position + rot * forward, rot * up);
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
	turnAngle += angle;
}

void Camera::lookUp (float angle)
{
	lookUpAngle += angle;
}

void Camera::tilt (float angle)
{
	tiltAngle += angle;
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

const glm::vec3 def_forward{ 0.0f,0.0f,1.0f };
const glm::vec3 def_up{ 0.0f,1.0f,0.0f };

