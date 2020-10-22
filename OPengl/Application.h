#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include<glm/ext/matrix_transform.hpp>

class Application
{
	private:
		const int WINDOW_WIDTH;
		const int WINDOW_HEIGHT;
		const glm::vec2 WINDOW_POSITION;
		Window window;
		Shader shader;
		Mesh mesh;

		float deltaTime;

		glm::mat4 model;
		glm::mat4 projection;

		void createPyramid();
		void start();
		Application();
	public:
		Application(const Application& ) = delete;
		static Application& Get();
		void update();
		~Application();


};

