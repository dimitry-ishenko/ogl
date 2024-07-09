#include <ogl/buffer.hpp>
#include <ogl/error.hpp>
#include <ogl/extern.hpp>

namespace ogl
{

vertex_buffer::vertex_buffer()
{
    glGenBuffers(1, &id_);
    if (int ev = glGetError()) throw opengl_error{ev};
}

vertex_buffer::~vertex_buffer() { glDeleteBuffers(1, &id_); }

void vertex_buffer::data(void* payload, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, size, payload, GL_STATIC_DRAW);
    if (int ev = glGetError()) throw opengl_error{ev};
}

}
