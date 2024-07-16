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
void vertex_buffer::create(const void* payload, std::size_t bytes)
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

////////////////////////////////////////////////////////////////////////////////
namespace
{

static constexpr unsigned no_index = -1;

constexpr auto calc_size(std::size_t vbo_size, std::size_t vbo_value_size, std::size_t elem_count, std::size_t off, std::size_t stride)
{
    auto bytes = vbo_size * vbo_value_size - off;
    // NB: stride_ can be 0 if data is packed
    if (!stride) stride = elem_count * vbo_value_size;

    return bytes / stride + ((bytes % stride) ? 1 : 0);
}

}

vertex_attr::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_count, unsigned type, std::size_t off, std::size_t stride, ogl::norm norm) :
    index_{index}, size_{ calc_size(vbo.size(), vbo.value_size(), elem_count, off, stride) }
{
    vertex_buffer::visitor::bind(vbo);

    glVertexAttribPointer(index, elem_count, type, norm, stride, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);

    vertex_buffer::visitor::unbind(vbo);
}

vertex_attr::~vertex_attr() { if (index_ != no_index) disable(); }

vertex_attr::vertex_attr(vertex_attr&& rhs) : index_{rhs.index_}, size_{rhs.size_} { rhs.index_ = no_index; }

vertex_attr& vertex_attr::operator=(vertex_attr&& rhs)
{
    vertex_attr::~vertex_attr();

    index_ = rhs.index_;
    size_ = rhs.size_;
    rhs.index_ = no_index;
    
    return (*this);
}

void vertex_attr::enable() { glEnableVertexAttribArray(index_); }
void vertex_attr::disable() { glDisableVertexAttribArray(index_); }

////////////////////////////////////////////////////////////////////////////////
}
