////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include <ogl/core.hpp>
#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/shader.hpp>
#include <ogl/vertex.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
void window_hint(version v)
{
    auto x = 3 + (v >> 0x08), y = v & 0xff;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, x);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, y);
}

void reset_window_hints() { glfwDefaultWindowHints(); }

void poll_events() { glfwPollEvents(); }
void wait_events() { glfwWaitEvents(); }

////////////////////////////////////////////////////////////////////////////////
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

void draw_trias(shader_program& pgm, vertex_attr_ptr& ptr, std::size_t from, std::size_t size)
{
    shader_program::visitor::use(pgm);
    vertex_attr_ptr::visitor::enable(ptr);

    glDrawArrays(GL_TRIANGLES, from, size);
    if (auto ev = glGetError()) throw opengl_error(ev);

    vertex_attr_ptr::visitor::disable(ptr);
}

////////////////////////////////////////////////////////////////////////////////
}
