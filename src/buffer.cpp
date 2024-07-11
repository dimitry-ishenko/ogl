#include <ogl/buffer.hpp>
#include <ogl/error.hpp>
#include <ogl/extern.hpp>

namespace ogl
{

vertex_buffer::vertex_buffer()
{
    glGenBuffers(1, &id_);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

vertex_buffer::~vertex_buffer() { glDeleteBuffers(1, &id_); }

vertex_buffer::vertex_buffer(vertex_buffer&& rhs) : id_{rhs.id_} { rhs.id_ = 0; }

vertex_buffer& vertex_buffer::operator=(vertex_buffer&& rhs)
{
    vertex_buffer::~vertex_buffer();
    id_ = rhs.id_;
    rhs.id_ = 0;
    return (*this);
}

void vertex_buffer::data(void* payload, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

}
