#include <ogl/vertex.hpp>
#include <ogl/error.hpp>
#include <ogl/extern.hpp>

namespace ogl
{

vertex_buffer::vertex_buffer(const void* payload, int size)
{
    glGenBuffers(1, &vbo_);
    if (auto ev = glGetError()) throw opengl_error(ev);

    bind();
    glBufferData(GL_ARRAY_BUFFER, size, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

vertex_buffer::~vertex_buffer() { glDeleteBuffers(1, &vbo_); }

void vertex_buffer::bind() { glBindBuffer(GL_ARRAY_BUFFER, vbo_); }
void vertex_buffer::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

}
