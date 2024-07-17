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
namespace
{

unsigned create()
{
    unsigned o;
    glGenBuffers(1, &o);
    if (auto ev = glGetError()) throw opengl_error(ev);

    return o;
}

void delete_(unsigned o) { glDeleteBuffers(1, &o); }

void bind(unsigned target, unsigned o) { glBindBuffer(target, o); }
void unbind(unsigned target) { glBindBuffer(target, 0); }

}

////////////////////////////////////////////////////////////////////////////////
vertex_buffer::vertex_buffer() : vbo_{create()} { }

vertex_buffer::~vertex_buffer() { delete_(vbo_); }

vertex_buffer::vertex_buffer(vertex_buffer&& rhs) :
    vbo_{rhs.vbo_},
    value_size_{rhs.value_size_}, elem_size_{rhs.elem_size_}, elem_count_{rhs.elem_count_},
    opengl_type_{rhs.opengl_type_}, size_{rhs.size_}
{
    rhs.vbo_ = 0;
    rhs.size_ = 0;
}

vertex_buffer& vertex_buffer::operator=(vertex_buffer&& rhs)
{
    vertex_buffer::~vertex_buffer();

    vbo_ = rhs.vbo_;
    value_size_ = rhs.value_size_;
    elem_size_  = rhs.elem_size_;
    elem_count_ = rhs.elem_count_;
    opengl_type_= rhs.opengl_type_;
    size_ = rhs.size_;

    rhs.vbo_ = 0;
    rhs.size_ = 0;

    return (*this);
}

void vertex_buffer::data(const void* payload, std::size_t bytes)
{
    bind();

    glBufferData(GL_ARRAY_BUFFER, bytes, payload, GL_STATIC_DRAW);
    if (auto ev = glGetError()) throw opengl_error(ev);

    unbind();
}

void vertex_buffer::bind() { ogl::bind(GL_ARRAY_BUFFER, vbo_); }
void vertex_buffer::unbind() { ogl::unbind(GL_ARRAY_BUFFER); }

////////////////////////////////////////////////////////////////////////////////
namespace { static constexpr unsigned no_index = -1; }

vertex_attr::vertex_attr(unsigned index, vertex_buffer& vbo, ogl::norm norm) :
    vertex_attr{ index, vbo, 0, vbo.elem_count_, vbo.value_size_, vbo.opengl_type_, norm }
{ }

vertex_attr::vertex_attr(unsigned index, vertex_buffer& vbo, packed_t, ogl::norm norm) :
    vertex_attr{ index, vbo, 0, vbo.elem_count_, 0, vbo.opengl_type_, norm }
{ }

vertex_attr::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_from, std::size_t elem_count, ogl::norm norm) :
    vertex_attr{ index, vbo, elem_from, elem_count, vbo.value_size_, vbo.opengl_type_, norm }
{ }

vertex_attr::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm norm) :
    vertex_attr{ index, vbo, elem_from, elem_count, 0, vbo.opengl_type_, norm }
{ }

vertex_attr::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm norm) :
    vertex_attr{ index, vbo, elem_from, elem_count, stride, vbo.opengl_type_, norm }
{ }

vertex_attr::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_from, std::size_t elem_count, std::size_t stride, unsigned opengl_type, ogl::norm norm) :
    index_{index}
{
    auto off = elem_from * vbo.elem_size_;

    auto bytes = vbo.size_ * vbo.value_size_ - off;
    if (!stride) stride = elem_count * vbo.value_size_; // stride can be 0 to indicate packed data

    size_ = bytes / stride + ((bytes % stride) ? 1 : 0);

    ////////////////////
    vbo.bind();

    glVertexAttribPointer(index, elem_count, opengl_type, norm, stride, reinterpret_cast<const void*>(off));
    if (auto ev = glGetError()) throw opengl_error(ev);

    vbo.unbind();
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

template<typename... Args>
inline void vertex_array::enable_attr(Args&&... args)
{
    bind();
    ogl::vertex_attr attr{ std::forward<Args>(args)... };
    attr.enable();
    unbind();
}

void vertex_array::vertex_attr(unsigned index, vertex_buffer& vbo, ogl::norm norm)
{
    enable_attr(index, vbo, norm);
}
void vertex_array::vertex_attr(unsigned index, vertex_buffer& vbo, packed_t, ogl::norm norm)
{
    enable_attr(index, vbo, packed, norm);
}
void vertex_array::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_from, std::size_t elem_count, ogl::norm norm)
{
    enable_attr(index, vbo, elem_from, elem_count, norm);
}
void vertex_array::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm norm)
{
    enable_attr(index, vbo, elem_from, elem_count, packed, norm);
}
void vertex_array::vertex_attr(unsigned index, vertex_buffer& vbo, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm norm)
{
    enable_attr(index, vbo, elem_from, elem_count, stride, norm);
}

////////////////////////////////////////////////////////////////////////////////
}
