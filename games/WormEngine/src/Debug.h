#ifdef CALCULATE_FPS
#include <GLFW/glfw3.h>

#define CALCULATE_FPS_IF_REQUIRED() \
    calculate_and_display_fps()

int num_frames = 0;
double start_time = glfwGetTime();

void calculate_and_display_fps()
{
        num_frames++;

        double end_time = glfwGetTime();
        if (end_time - start_time >= 1.0f)
        {
            std::cout << "fps: " << num_frames << std::endl;
            start_time = glfwGetTime();
            num_frames=0;
        }
}

#else

#define CALCULATE_FPS_IF_REQUIRED()

#endif

