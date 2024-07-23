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
namespace { static constexpr unsigned no_index = -1; }

vertex_attr::vertex_attr(unsigned index, std::size_t size, std::size_t count, type opengl_type, ogl::norm norm, std::size_t stride, std::size_t off) :
    index_{index}, size_{size}
{
    glVertexAttribPointer(index_, count, opengl_type, norm, stride, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);
}

vertex_attr::vertex_attr(vertex_attr&& rhs) : index_{rhs.index_}, size_{rhs.size_}
{
    rhs.index_ = no_index;
    rhs.size_ = 0;
}

vertex_attr& vertex_attr::operator=(vertex_attr&& rhs)
{
    vertex_attr::~vertex_attr();
    index_ = rhs.index_;
    size_ = rhs.size_;

    rhs.index_ = no_index;
    rhs.size_ = 0;
    return (*this);
}

void vertex_attr::enable()  { if (index_ != no_index) glEnableVertexAttribArray(index_); }
void vertex_attr::disable() { if (index_ != no_index) glDisableVertexAttribArray(index_); }

////////////////////////////////////////////////////////////////////////////////
namespace internal
{

unsigned create_buffer()
{
    unsigned name;
    glGenBuffers(1, &name);
    if (auto ev = glGetError()) throw opengl_error(ev);

    return name;
}

void delete_buffer(unsigned name) { glDeleteBuffers(1, &name); }

void bind_buffer(unsigned target, unsigned name) { glBindBuffer(target, name); }
void unbind_buffer(unsigned target) { glBindBuffer(target, 0); }

void buffer_data(unsigned target, const void* payload, std::size_t bytes)
{
    glBufferData(target, bytes, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

const unsigned array_target = GL_ARRAY_BUFFER;
const unsigned element_target = GL_ELEMENT_ARRAY_BUFFER;

}

////////////////////////////////////////////////////////////////////////////////
vertex_array::vertex_array()
{
    glGenVertexArrays(1, &vao_);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

vertex_array::~vertex_array() { glDeleteVertexArrays(1, &vao_); }

vertex_array::vertex_array(vertex_array&& rhs) : vao_{rhs.vao_}, ebo_{rhs.ebo_} { rhs.vao_ = 0; }

vertex_array& vertex_array::operator=(vertex_array&& rhs)
{
    this->~vertex_array();
    vao_ = rhs.vao_;
    ebo_ = rhs.ebo_;

    rhs.vao_ = 0;
    return (*this);
}

void vertex_array::bind() { glBindVertexArray(vao_); }
void vertex_array::unbind() { glBindVertexArray(0); }

////////////////////////////////////////////////////////////////////////////////
}
