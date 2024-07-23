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
#include <ogl/types.hpp>
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

void draw_elem_trias(type opengl_type, std::size_t count, std::size_t off)
{
    glDrawElements(GL_TRIANGLES, count, opengl_type, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);
}

void draw_trias(shader_program& pgm, vertex_attr& attr, std::size_t from, std::size_t count)
{
    pgm.use();
    enable_guard enable{attr};
    draw_trias(from, count);
}

void draw_trias(shader_program& pgm, vertex_array& vao, std::size_t from, std::size_t count)
{
    pgm.use();
    bind_guard bind{vao};

    if (vao.ebo().bound)
        draw_elem_trias(vao.ebo().opengl_type, count, from * vao.ebo().value_size);
    else draw_trias(from, count);
}

////////////////////////////////////////////////////////////////////////////////
}
