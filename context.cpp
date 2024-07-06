#include "context.hpp"
#include "error.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ogl
{

context::context()
{
    glfwSetErrorCallback([](int ev, const char*) { throw opengl_error{ev}; });
    glfwInit();
}

context::~context() { glfwTerminate(); }

void context::poll_events() { glfwPollEvents(); }
void context::wait_events() { glfwWaitEvents(); }

void context::viewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

}
