#include "Camera.h"

glm::mat4 Camera::getViewMat()
{
	return glm::lookAt(position, position + n, v);
}

Camera::Camera(GLFWwindow* window)
	:window(window),
	position(glm::vec3(0.f, 0.f, 5.f)),
	u(glm::vec3(1.f, 0.f, 0.f)),
	v(glm::vec3(0.f, 1.f, 0.f)),
	n(glm::vec3(0.f, 0.f, -1.f)),
	yaw(-90.f),
	pitch(0),
	moveSpeed(10.f),
	mouse(Mouse::getInstance(window)),
	keyboard(Keyboard::getInstance(window))
{
	
}

void Camera::mouseInput()
{
	glm::vec2 cameraRotation = mouse.getChange();

	yaw += cameraRotation.x;
	pitch += cameraRotation.y;

	//clamping value of pitch between -90 and 90
	if (pitch <= -90.f)
	{
		pitch = -89.9f;
	}
	else if(pitch >= 90.f)
	{
		pitch = 89.9f;
	}

	n.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	n.y = sin(glm::radians(pitch));
	n.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	u = glm::cross(glm::vec3(n), glm::vec3(0.f, 1.f, 0.f));

	v = glm::cross(glm::vec3(u), glm::vec3(n));
}

void Camera::keyboardInput(float deltaTime)
{
	if (keyboard.isKeyDown(GLFW_KEY_W))
	{
		position += n * moveSpeed*deltaTime;
	}
	else if (keyboard.isKeyDown(GLFW_KEY_S))
	{
		position -= n * moveSpeed*deltaTime;
	}
	else if (keyboard.isKeyDown(GLFW_KEY_A))
	{
		position -= u * moveSpeed*deltaTime;
	}
	else if (keyboard.isKeyDown(GLFW_KEY_D))
	{
		position += u * moveSpeed*deltaTime;
	}
}

void Camera::update(float deltaTime)
{
	mouseInput();
	keyboardInput(deltaTime);
}
