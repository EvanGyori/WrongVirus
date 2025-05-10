#include "Window.h"

#include <stdexcept>

Window::Window()
{
    GLFWmanager::initVulkanAndGLFW();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    
    window = glfwCreateWindow(500, 500, "I DID IT!!", nullptr, nullptr);
    if (window == nullptr) {
	throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowOpacity(window, 0.3f);
}

Window::~Window()
{
    glfwDestroyWindow(window);
}

GLFWwindow* Window::getHandle()
{
    return window;
}
