#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
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

		glm::mat4 model;
		glm::mat4 projection;

		void createPyramid();
	public:
		void start();
		void update();
		Application();
		~Application();


};

