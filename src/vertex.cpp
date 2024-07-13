#include <ogl/vertex.hpp>
#include <ogl/error.hpp>
#include <ogl/extern.hpp>

namespace ogl
{

vertex_buffer::vertex_buffer(const void* payload, std::size_t size)
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

vertex_array::vertex_array()
{
    glGenVertexArrays(1, &vao_);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

void vertex_array::enable_attr(const vertex_attr& attr)
{
    attr.buffer.bind();

    glVertexAttribPointer(attr.index, attr.count, attr.type, attr.norm, attr.stride,
        reinterpret_cast<void*>(attr.offset)
    );
    if (auto ev = glGetError()) throw opengl_error(ev);

    glEnableVertexAttribArray(attr.index);
}

void vertex_array::bind() { glBindVertexArray(vao_); }
void vertex_array::unbind() { glBindVertexArray(0); }

}
