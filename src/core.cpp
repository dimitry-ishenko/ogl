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

void clear(const color& c)
{
    glClearColor(c.r(), c.g(), c.b(), c.a());
    glClear(GL_COLOR_BUFFER_BIT);
}

////////////////////////////////////////////////////////////////////////////////
void draw_trias(shader_program& pgm, vertex_attr& attr, std::size_t from, std::size_t count)
{
    pgm.use();
    attr.enable();

    glDrawArrays(GL_TRIANGLES, from, count);
    if (auto ev = glGetError()) throw opengl_error(ev);

    attr.disable();
}

void draw_trias(shader_program& pgm, vertex_attr& attr, element_buffer& ebo, std::size_t from, std::size_t count)
{
    pgm.use();
    attr.enable();
    ebo.bind();

    glDrawElements(GL_TRIANGLES, count, ebo.opengl_type_, reinterpret_cast<const void*>(from * ebo.value_size_));
    if (auto ev = glGetError()) throw opengl_error(ev);

    ebo.unbind();
    attr.disable();
}

void draw_trias(shader_program& pgm, vertex_array& vao, std::size_t from, std::size_t count)
{
    pgm.use();
    vao.bind();

    if (vao.ebo_)
    {
        glDrawElements(GL_TRIANGLES, count, vao.ebo_->opengl_type_, reinterpret_cast<const void*>(from * vao.ebo_->value_size_));
        if (auto ev = glGetError()) throw opengl_error(ev);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, from, count);
        if (auto ev = glGetError()) throw opengl_error(ev);
    }

    vao.unbind();
}

////////////////////////////////////////////////////////////////////////////////
}
