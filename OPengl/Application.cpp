#include "Application.h"
#include "assimp/Importer.hpp"

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

    float floor[] = {
        //Positions          //Normals          //textureCoordinates
       -10.f, -1.1f, -10.f,     0.f, -1.f, 0.f,     0.f,  0.f,     //0
       -10.f, -1.1f,  10.f,     0.f, -1.f, 0.f,     0.f,  1.f,    //1
        10.f, -1.1f, -10.f,     0.f, -1.f, 0.f,     1.f,  0.f,     //2
        10.f, -1.1f,  10.f,     0.f, -1.f, 0.f,     1.f, 1.f      //3

    };

    uint32_t floorIndex[] = {
        0,1,2,
        1,2,3
    };

    shader.create("vertexShader.glsl", "fragmentShader.glsl");

    Helper::calculateVertexNormal(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(uint32_t), 8, 3);

    mesh.create(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(uint32_t),shader.getProgram());

    
    m1.create(floor, sizeof(floor) / sizeof(float), floorIndex, sizeof(floorIndex) / sizeof(uint32_t), shader.getProgram());
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    glBlendEquation(GL_ADD);

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
    Material dmaterial(shader.getProgram(), 0.1f, 0.3f, 1.f, 64);
    Material smaterial(shader.getProgram(), 0.1f, 0.6f, 1.f, 256);

    Texture dText = Texture(shader.getProgram(), "textures/index.png",0);
    Texture sText = Texture(shader.getProgram(), "textures/index.png", 1);
   

    Model test;
    test.load("models/gun/wooden watch tower2.obj", shader.getProgram());


    glm::mat4 mod = glm::mat4(1.f);
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

        


        //model = glm::rotate(model, glm::radians(currAngle), glm::vec3(0.f, 1.f, 0.f));
        //model = glm::translate(model, glm::vec3(dir * xTrans, 0.f, 0.f));

        /* Poll for and process events */
        glfwPollEvents();



        /* Render here */
        
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //updating camera
        camera.update(deltaTime,&projection);

        //updating material
        

        //updating lights
        light.update(glm::vec3(1.f, 1.f, 1.f), glm::vec3(-1.f, -3.f, 0.f));

        //Update and render mesh
        dText.Activate();
        //sText.Activate();
        smaterial.update();
        mesh.update(&model);
        mesh.render();

        glm::mat4 model1 = glm::mat4(1.f);
        
        currAngle = currAngle > 360 ? 0 : 1.f;
        //model1 = glm::rotate(model1, glm::radians(currAngle), glm::vec3(0.f, 1.f, 0.f));
        model1 = glm::translate(model1, glm::vec3(0.f, -1.5f, 0.f));
        
        test.render(&model1);

        dmaterial.update();
        dText.Activate();
        sText.Activate();
        m1.update(&mod);
        m1.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window.getWindow());


    }
}

Application& Application::Get()
{
    static Application instance;
    return instance;
}