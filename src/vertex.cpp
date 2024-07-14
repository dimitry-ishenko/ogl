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

vertex_buffer::vertex_buffer(const void* payload, std::size_t bytes) : bytes_{bytes}
{
    glGenBuffers(1, &vbo_);
    if (auto ev = glGetError()) throw opengl_error(ev);

    bind();

    glBufferData(GL_ARRAY_BUFFER, bytes, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);

    unbind();
}

vertex_buffer::~vertex_buffer() { glDeleteBuffers(1, &vbo_); }

vertex_buffer::vertex_buffer(vertex_buffer&& rhs) : vbo_{rhs.vbo_} { rhs.vbo_ = 0; }

vertex_buffer& vertex_buffer::operator=(vertex_buffer&& rhs)
{
    vertex_buffer::~vertex_buffer();
    vbo_ = rhs.vbo_;
    rhs.vbo_ = 0;
    return (*this);
}

void vertex_buffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, vbo_); }
void vertex_buffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

}

////////////////////////////////////////////////////////////////////////////////
}
