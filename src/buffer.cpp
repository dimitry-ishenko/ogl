#include <ogl/buffer.hpp>
#include <ogl/error.hpp>
#include <ogl/extern.hpp>

namespace ogl
{

vertex_buffer::vertex_buffer()
{
    glGenBuffers(1, &vbo_);
    if (auto ev = glGetError()) throw opengl_error(ev);
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

void vertex_buffer::data(const void* payload, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, size, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

}
