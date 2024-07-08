#include <ogl/core.hpp>
#include <ogl/extern.hpp>

namespace ogl
{

void window_hint(version v)
{
    auto x = 3 + (v >> 0x08), y = v & 0xff;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, x);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, y);
}

void reset_window_hints() { glfwDefaultWindowHints(); }

void poll_events() { glfwPollEvents(); }
void wait_events() { glfwWaitEvents(); }

void viewport(int x, int y, int width, int height) { glViewport(x, y, width, height); }

void clear(const color& c)
{
    glClearColor(c.r(), c.g(), c.b(), c.a());
    glClear(GL_COLOR_BUFFER_BIT);
}


}
