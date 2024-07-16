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
namespace detail
{

unsigned xbo_create()
{
    unsigned xbo;
    glGenBuffers(1, &xbo);
    if (auto ev = glGetError()) throw opengl_error(ev);

    return xbo;
}

////////////////////////////////////////////////////////////////////////////////
unsigned vbo_create(const void* payload, std::size_t bytes)
{
    unsigned vbo = xbo_create();

    vbo_bind(vbo);

    glBufferData(GL_ARRAY_BUFFER, bytes, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);

    vbo_unbind();

    return vbo;
}

void vbo_delete(unsigned vbo) { glDeleteBuffers(1, &vbo); }

void vbo_bind(unsigned vbo) { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
void vbo_unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

}

////////////////////////////////////////////////////////////////////////////////
namespace { static constexpr unsigned no_index = -1; }

vertex_attr::vertex_attr(unsigned index, unsigned vbo, std::size_t vbo_size, std::size_t vbo_value_size, std::size_t vbo_elem_size,
    std::size_t elem_from, std::size_t elem_count, std::size_t stride, unsigned type, ogl::norm norm) : index_{index}
{
    auto off = elem_from * vbo_elem_size;

    auto bytes = vbo_size * vbo_value_size - off;
    if (!stride) stride = elem_count * vbo_value_size; // stride can be 0 to indicate packed data

    size_ = bytes / stride + ((bytes % stride) ? 1 : 0);

    ////////////////////
    detail::vbo_bind(vbo);

    glVertexAttribPointer(index, elem_count, type, norm, stride, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);

    detail::vbo_unbind();
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
vertex_array::vertex_array()
{
    glGenVertexArrays(1, &vao_);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

vertex_array::~vertex_array() { glDeleteVertexArrays(1, &vao_); }

vertex_array::vertex_array(vertex_array&& rhs) : vao_{rhs.vao_} { rhs.vao_ = 0; }

vertex_array& vertex_array::operator=(vertex_array&& rhs)
{
    vertex_array::~vertex_array();
    vao_ = rhs.vao_;
    rhs.vao_ = 0;
    return (*this);
}

void vertex_array::bind() { glBindVertexArray(vao_); }
void vertex_array::unbind() { glBindVertexArray(0); }

////////////////////////////////////////////////////////////////////////////////
}
