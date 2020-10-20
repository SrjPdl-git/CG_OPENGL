#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/ext/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"

#define PI 3.1415927
#define TO_RADIANS(x) ((PI*x)/180)


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WINDOW_POS_X = 100;
const int WINDOW_POS_Y = 50;

//unsigned int vertexArrayObject;
//unsigned int  vertexBufferObject;
unsigned int uColor;

float rainbow;
float xTrans = 0.005f;
float dir = -1.f;
float xOffset = -0.5f;

float currAngle = 0.f;

uint32_t uModel;
uint32_t uProjection;

Mesh mesh;

void createTriangle()
{
    float positions[] = {
      -1.f, -1.f,  0.f,//0
       0.f, -1.f,  1.f,//1
       1.f, -1.f,  0.f,//2
       0.f,  1.f,  0.f//3
    };

    uint32_t indices[] = {
        0,3,1,
        1,3,2,
        2,3,0,
        0,1,2
    };

    Shader shader;
    uint32_t shaderProgram=shader.create("vertexShader.shader", "fragmentShader.shader");
    
    mesh.create(positions, sizeof(positions) / sizeof(float), indices, sizeof(indices) / sizeof(uint32_t));

    uColor = glGetUniformLocation(shaderProgram, "uColour");
    uModel = glGetUniformLocation(shaderProgram, "model");
    uProjection = glGetUniformLocation(shaderProgram, "projection");


}

int main()
{


    GLFWwindow* window;

    /* Initialize GLFW */
    if (!glfwInit())
    {   
        std::cout << "ERROR::FAILED_TO_INITIALIZE_GLFW" << std::endl;
        return 0;
    }

    /*GLFW Hints*/
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Opengl Window", NULL, NULL);
    
    if (!window)
    {
        std::cout << "ERROR::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();
        return 0;
    }

    /*Set Window Position*/
    glfwSetWindowPos(window, WINDOW_POS_X, WINDOW_POS_Y);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Get frame buffer size and set viewport
    int frameBufferWidth, frameBufferHeight;
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    /*Initialize GLEW*/
   if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::FAILED_TO_INITIALIZE_GLEW" << std::endl;
        glfwTerminate();
        return 0;
    }
   glewExperimental = GL_TRUE;
   glEnable(GL_DEPTH_TEST);

   glfwSwapInterval(1);


     /*Modern opengl stuff*/
     createTriangle();
     
     glm::mat4 model(1.0f);
     model = glm::translate(model, glm::vec3(0.f, 0.f, -3.f));
     model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));

     glm::mat4 projection = glm::perspective<float>(45.f, (float)frameBufferWidth / frameBufferHeight, 1.f, 100.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        rainbow = sin(glfwGetTime());

        xOffset = xOffset + (dir * xTrans);
        if (fabs(xOffset) >=1)
        {
            dir *= -1;
        }

        currAngle = currAngle > 360 ? 0 : 1.f;

        
        model = glm::rotate(model,glm::radians(currAngle), glm::vec3(0.f, 1.f, 0.f));
        //model = glm::translate(model, glm::vec3(dir * xTrans, 0.f, 0.f));
        
        /* Poll for and process events */
        glfwPollEvents();



        /* Render here */
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4f(uColor, 0.f, 1.f, 0.f,1.f);
        
        mesh.render();
        //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

        /*Draw Triangle*/
        /*Legacy opengl*/
        /*glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.f,0.5f    );
        glVertex2f(0.5f, -0.5f); 
        glEnd();
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        
    }
    glfwTerminate();
    return 0;
}