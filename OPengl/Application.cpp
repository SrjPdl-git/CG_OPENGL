#include "Application.h"

Application::Application()
	:WINDOW_WIDTH(800),
	 WINDOW_HEIGHT(600),
	 WINDOW_POSITION(glm::vec2(100,50)),
     model(glm::mat4(1.0f)),
     projection(NULL),
     deltaTime(NULL)
{
	setup();
}

Application::~Application()
{
}

void Application::createPyramid()
{
    float vertices[] = {
       //Positions          //Normals          //textureCoordinates
      -1.f, -1.f,  0.f,     0.f, 0.f, 0.f,     0.f,  0.f,     //0
       0.f, -1.f,  1.f,     0.f, 0.f, 0.f,     0.5f, 0.f,    //1
       1.f, -1.f,  0.f,     0.f, 0.f, 0.f,     1.f,  0.f,     //2
       0.f,  1.f,  0.f,     0.f, 0.f, 0.f,     0.5f, 1.f      //3
    };

    uint32_t indices[] = {
        0,3,1,
        1,3,2,
        2,3,0,
        0,1,2
    };


    shader.create("vertexShader.glsl", "fragmentShader.glsl");

    Helper::calculateVertexNormal(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(uint32_t), 8, 3);

    mesh.create(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(uint32_t),"textures/index.png",shader.getProgram());

}

void Application::setup()
{    
    window.create("Opengl Project", WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_POSITION);


    /*Initialize GLEW*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::FAILED_TO_INITIALIZE_GLEW" << std::endl;
        glfwTerminate();
    }
    glewExperimental = GL_TRUE;
    glEnable(GL_DEPTH_TEST);

    //Setting buffer swap interval
    glfwSwapInterval(1);

    createPyramid();

    model = glm::translate(model, glm::vec3(0.f, 0.f, -3.f));
    model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
    projection = glm::perspective<float>(45.f, window.getViewportAspectRatio(), 1.f, 100.f);
}

void Application::update()
{   
    float lastFrameTime = 0.f;
    float currentFrameTime = 0.f;

    float rainbow;
    float xTrans = 0.005f;
    float dir = -1.f;
    float xOffset = -0.5f;

    float currAngle = 0.f;
   
    Camera camera(window.getWindow(),shader.getProgram());
    Light light(shader.getProgram());
    Material material(shader.getProgram());

    while (window.isOpen())
    {
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        //std::cout << 1 / deltaTime << std::endl;

        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
        }

        projection = glm::perspective<float>(45.f, window.getViewportAspectRatio(), 1.f, 100.f);

        rainbow = sin(glfwGetTime());

        xOffset = xOffset + (dir * xTrans);
        if (fabs(xOffset) >= 1)
        {
            dir *= -1;
        }

        currAngle = currAngle > 360 ? 0 : 1.f;


        //model = glm::rotate(model, glm::radians(currAngle), glm::vec3(0.f, 1.f, 0.f));
        //model = glm::translate(model, glm::vec3(dir * xTrans, 0.f, 0.f));

        /* Poll for and process events */
        glfwPollEvents();



        /* Render here */
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //updating camera
        camera.update(deltaTime,&projection);

        //updating material
        material.update(1.f, 64);

        //updating lights
        light.update(glm::vec3(1.f, 1.f, 1.f),0.3f, 0.4f, glm::vec3(-1.f, -1.f, 0.f));

        //Update and render mesh
        mesh.update(&model);
        mesh.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window.getWindow());


    }
}

Application& Application::Get()
{
    static Application instance;
    return instance;
}