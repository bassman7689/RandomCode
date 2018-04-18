#include <iostream>

#include "Window.h"

void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error[%d]: %s\n", error, description);
}

void WindowResizeCallback(GLFWwindow *window, int width, int height)
{
   glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

Window::Window(int width, int height, std::string title) : _width(width), _height(height), _title(title)
{
}

Window::~Window()
{
    glfwTerminate();
}

void Window::init()
{
    if (glfwInit() == GLFW_FALSE)
    {
        fprintf(stderr, "Couldn't initialize glfw\n");
        exit(1);
    }

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

    if(_window == NULL)
    {
        glfwTerminate();

        fprintf(stderr, "Failed to create GLFW Window!\n");
        exit(1);
    }

    glfwMakeContextCurrent(_window);

    WindowResizeCallback(_window, _width, _height);
    glfwSetWindowSizeCallback(_window, WindowResizeCallback);

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if(status != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW!");
        exit(1);
    }
}

void Window::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_window);
}

