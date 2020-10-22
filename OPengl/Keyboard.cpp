#include "Keyboard.h"

uint32_t Keyboard::key = NULL;

Keyboard::Keyboard(GLFWwindow* window)
    :window(window)
{
    //glfwSetKeyCallback(window, handleKeyboard);
}

void Keyboard::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GL_REPEAT)
    {
        Keyboard::key = key;
    }
}

Keyboard& Keyboard::getInstance(GLFWwindow* window)
{
    static Keyboard instance(window);
    return instance;
}

bool Keyboard::isKeyDown(uint32_t key)
{
    bool action=glfwGetKey(window, key);
    return (action== (GLFW_PRESS || GLFW_REPEAT));
}
