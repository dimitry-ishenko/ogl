#include <ogl/core.hpp>
#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/shader.hpp>
#include <ogl/vertex.hpp>

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

void viewport(int x, int y, unsigned width, unsigned height)
{
    glViewport(x, y, width, height);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

void clear(const color& c)
{
    glClearColor(c.r(), c.g(), c.b(), c.a());
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw(shader_program& pgm, vertex_attr& attr, std::size_t from) { draw(pgm, attr, from, attr.buf_->bytes_ / attr.stride_); }

void draw(shader_program& pgm, vertex_attr& attr, std::size_t from, std::size_t size)
{
    pgm.use();
    attr.enable();

    glDrawArrays(GL_TRIANGLES, from, size);
    if (auto ev = glGetError()) throw opengl_error(ev);

    attr.disable();
}

}
