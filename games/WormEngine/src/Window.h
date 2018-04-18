#ifndef __WINDOW__
#define __WINDOW__

#include <cstdlib>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window{
public:
    Window(int width, int height, std::string title);
    ~Window();

    void init();
    void clear();
    bool shouldClose() { return glfwWindowShouldClose(_window); }
    void swapBuffers();

private:
    int _width;
    int _height;
    std::string _title;
    
    GLFWwindow *_window;
};

#endif
