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
void poll_events() { glfwPollEvents(); }
void wait_events() { glfwWaitEvents(); }

////////////////////////////////////////////////////////////////////////////////
void viewport(int x, int y, unsigned width, unsigned height)
{
    glViewport(x, y, width, height);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

void clear(const color4& c)
{
    glClearColor(c.r(), c.g(), c.b(), c.a());
    glClear(GL_COLOR_BUFFER_BIT);
}

////////////////////////////////////////////////////////////////////////////////
void draw_trias(std::size_t from, std::size_t count)
{
    glDrawArrays(GL_TRIANGLES, from, count);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

void draw_trias(shader_program& pgm, vertex_attr& attr, std::size_t from, std::size_t count)
{
    pgm.use();
    attr.enable();
    draw_trias(from, count);
    attr.disable();
}

namespace internal
{
void draw_ebo_trias(unsigned count, type opengl_type, std::size_t off)
{
    glDrawElements(GL_TRIANGLES, count, opengl_type, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);
}
}

void draw_trias(shader_program& pgm, vertex_array& vao, std::size_t from, std::size_t count)
{
    pgm.use();
    vao.bind();

    if (vao.ebo().bound)
    {
        glDrawElements(GL_TRIANGLES, count, vao.ebo().opengl_type, reinterpret_cast<const void*>(from * vao.ebo().value_size));
        if (auto ev = glGetError()) throw opengl_error(ev);
    }
    else draw_trias(from, count);

    vao.unbind();
}

////////////////////////////////////////////////////////////////////////////////
}
