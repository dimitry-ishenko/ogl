#include "context.hpp"
#include "error.hpp"
#include "window.hpp"

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

void context::window_hint(version ver)
{
    auto x = 3 + (ver >> 0x08), y = ver & 0xff;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, x);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, y);
}

void context::reset_window_hints() { glfwDefaultWindowHints(); }

window context::create_window(int width, int height, std::string_view title)
{
    return window{width, height, title};
}

void context::poll_events() { glfwPollEvents(); }
void context::wait_events() { glfwWaitEvents(); }

void context::viewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void context::clear_color(color&& c) { glClearColor(c.r(), c.g(), c.b(), c.a()); }

void context::clear() { glClear(GL_COLOR_BUFFER_BIT); }

}
