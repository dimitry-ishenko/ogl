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
vertex_buffer_base::vertex_buffer_base(const void* payload, std::size_t bytes) : bytes{bytes}
{
    glGenBuffers(1, &vbo);
    if (auto ev = glGetError()) throw opengl_error(ev);

    bind();

    glBufferData(GL_ARRAY_BUFFER, bytes, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);

    unbind();
}

vertex_buffer_base::~vertex_buffer_base() { glDeleteBuffers(1, &vbo); }

vertex_buffer_base::vertex_buffer_base(vertex_buffer_base&& rhs) : vbo{rhs.vbo} { rhs.vbo = 0; }

vertex_buffer_base& vertex_buffer_base::operator=(vertex_buffer_base&& rhs)
{
    vertex_buffer_base::~vertex_buffer_base();
    vbo = rhs.vbo;
    rhs.vbo = 0;
    return (*this);
}

void vertex_buffer_base::bind() { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
void vertex_buffer_base::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

////////////////////////////////////////////////////////////////////////////////
namespace { static constexpr unsigned invalid_index = -1; }

vertex_attr::vertex_attr(vertex_buffer_base& buf, unsigned index, std::size_t size, unsigned type, ogl::norm norm, std::size_t stride, std::ptrdiff_t off) :
    index{index}
{
    buf.bind();

    glVertexAttribPointer(index, size, type, norm, stride, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);

    buf.unbind();
}

vertex_attr::vertex_attr(vertex_attr&& rhs) : index{rhs.index} { rhs.index = invalid_index; }

vertex_attr& vertex_attr::operator=(vertex_attr&& rhs)
{
    vertex_attr::~vertex_attr();

    index = rhs.index;
    rhs.index = invalid_index;

    return (*this);
}

void vertex_attr::enable() const { if (index != invalid_index) glEnableVertexAttribArray(index); }
void vertex_attr::disable() const { if (index != invalid_index) glDisableVertexAttribArray(index); }

////////////////////////////////////////////////////////////////////////////////
}
