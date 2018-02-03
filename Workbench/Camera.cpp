#include "Camera.hpp"
#include <glm.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>



Camera::Camera () : viewportWidth{ 1 }, viewportHeight{ 1 }, 
					roll{ 0 }, pitch{ 0 }, yaw{0},
					length { 1.0f }, fov{ 45.0f }, target ()
{

}


Camera::~Camera ()
{
}


void Camera::calculate ()
{
	constexpr float nearPlane = 1.0f;
	constexpr float farPlane = 10.0f;
	glm::mat4 matRoll = glm::mat4 (1.0f);
	glm::mat4 matPitch = glm::mat4 (1.0f);
	glm::mat4 matYaw = glm::mat4 (1.0f);
	matRoll = glm::rotate (matRoll, glm::radians(roll), glm::vec3 (1.0f, 0.0f, 0.0f));
	matPitch = glm::rotate (matPitch, glm::radians (pitch), glm::vec3 (0.0f, 1.0f, 0.0f));
	matYaw = glm::rotate (matYaw, glm::radians (yaw), glm::vec3 (0.0f, 0.0f,1.0f));
	glm::mat4 rotate = matRoll * matPitch * matYaw;
	glm::mat4 translate = glm::mat4 (1.0f);
	translate = glm::translate (translate, glm::vec3(0.0f,-1.2f,-4.0f));
	glm::mat4 view = translate * rotate;
	float aspectRatio = viewportWidth / static_cast<float>(viewportHeight);
	glm::mat4 projection = glm::perspective (glm::radians(fov), aspectRatio, nearPlane, farPlane);
	combined = projection * view;
}

const float * Camera::get ()
{
	return glm::value_ptr(combined);
}
