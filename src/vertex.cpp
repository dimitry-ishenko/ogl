////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/vertex.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
namespace internal
{

vertex_buffer::vertex_buffer(const void* payload, std::size_t bytes) : bytes{bytes}
{
    glGenBuffers(1, &vbo);
    if (auto ev = glGetError()) throw opengl_error(ev);

    bind();

    glBufferData(GL_ARRAY_BUFFER, bytes, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);

    unbind();
}

vertex_buffer::~vertex_buffer() { glDeleteBuffers(1, &vbo); }

vertex_buffer::vertex_buffer(vertex_buffer&& rhs) : vbo{rhs.vbo} { rhs.vbo = 0; }

vertex_buffer& vertex_buffer::operator=(vertex_buffer&& rhs)
{
    vertex_buffer::~vertex_buffer();
    vbo = rhs.vbo;
    rhs.vbo = 0;
    return (*this);
}

void vertex_buffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
void vertex_buffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

}

////////////////////////////////////////////////////////////////////////////////
vertex_attr::vertex_attr(vertex_attr&& rhs) :
    buf{rhs.buf}, index{rhs.index}, element_size{rhs.element_size}, element_type{rhs.element_type}, norm{rhs.norm}, stride{rhs.stride}, off{rhs.off}, created{rhs.created}
{
    rhs.buf = nullptr;
    rhs.created = false;
}

vertex_attr& vertex_attr::operator=(vertex_attr&& rhs)
{
    vertex_attr::~vertex_attr();

    buf = rhs.buf;
    index = rhs.index;
    element_size = rhs.element_size;
    element_type = rhs.element_type;
    norm = rhs.norm;
    stride = rhs.stride;
    off = rhs.off;
    created = rhs.created;

    rhs.buf = nullptr;
    rhs.created = false;

    return (*this);
}

void vertex_attr::create()
{
    buf->bind();

    glVertexAttribPointer(index, element_size, element_type, norm, stride, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);

    buf->unbind();
}

void vertex_attr::enable()
{
    if (!created) { create(); created = true; }
    glEnableVertexAttribArray(index);
}

void vertex_attr::disable()
{
    if (created) glDisableVertexAttribArray(index);
}

////////////////////////////////////////////////////////////////////////////////
}
