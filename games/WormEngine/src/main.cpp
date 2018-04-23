#define GLEW_STATIC

#include <iostream>
#include <cmath>

#include "Graphics.h"

#define CALCULATE_FPS // has to be defined before including debug to work
#include "Debug.h"

#define WIDTH 1024
#define HEIGHT 768
#define TITLE "OpenGLTut"


int main()
{
    std::unique_ptr<Window> window = std::make_unique<Window>(WIDTH, HEIGHT, TITLE);
    window->init();

    std::shared_ptr<Shader> shader = std::make_shared<Shader>("res/basic.vert", "res/basic.frag");
    Sprite *square = new Sprite(WIDTH/2-512, HEIGHT/2-288, "res/simple.png", shader);
    square->scale(0.5f, 0.5f);
    square->rotate(90.0f);

    while(!window->shouldClose())
    {
        glfwPollEvents();

        window->clear();

        square->draw();

        window->swapBuffers();

        CALCULATE_FPS_IF_REQUIRED();
    }
}

