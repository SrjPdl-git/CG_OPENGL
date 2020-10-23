#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Mouse.h"
#include "Keyboard.h"
class Camera
{

	private:
		GLFWwindow* window;
		glm::vec3 position;
		glm::vec3 u;
		glm::vec3 v;
		glm::vec3 n;
		float yaw;
		float pitch;
		float moveSpeed;
		
		Mouse& mouse;
		Keyboard& keyboard;

		void mouseInput();
		void keyboardInput(float deltaTime);
	public:
		Camera(GLFWwindow* window);

		void update(float deltaTime);
		glm::mat4 getViewMat();
		
};

