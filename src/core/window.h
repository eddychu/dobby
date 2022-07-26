#pragma once
#include "math/vector2.h"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
class Window
{
public:
    static void resize_callback(GLFWwindow *window, int width, int height);

    Window(const int &width, const int &height, const std::string &title);

    GLFWwindow *get_handle()
    {
        return m_window;
    }

    bool should_close()
    {
        return glfwWindowShouldClose(m_window);
    }

    void poll_events()
    {
        glfwPollEvents();
    }

    Vector2I get_frame_buffer_size()
    {
        Vector2I size(0, 0);
        glfwGetFramebufferSize(m_window, &size.x, &size.y);
        return size;
    }

private:
    GLFWwindow *m_window;
    bool is_resized = false;
    int width;
    int height;
};
