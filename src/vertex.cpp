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
vertex_attr::vertex_attr(vertex_attr&& rhs) :
    buf_{rhs.buf_}, index_{rhs.index_}, element_size_{rhs.element_size_}, element_type_{rhs.element_type_},
    norm_{rhs.norm_}, stride_{rhs.stride_}, off_{rhs.off_}, created_{rhs.created_}
{
    rhs.buf_ = nullptr;
    rhs.created_ = false;
}

vertex_attr& vertex_attr::operator=(vertex_attr&& rhs)
{
    vertex_attr::~vertex_attr();

    buf_ = rhs.buf_;
    index_ = rhs.index_;
    element_size_ = rhs.element_size_;
    element_type_ = rhs.element_type_;
    norm_ = rhs.norm_;
    stride_ = rhs.stride_;
    off_ = rhs.off_;
    created_ = rhs.created_;

    rhs.buf_ = nullptr;
    rhs.created_ = false;

    return (*this);
}

void vertex_attr::create()
{
    buf_->bind();

    glVertexAttribPointer(index_, element_size_, element_type_, norm_, stride_, reinterpret_cast<const void*>(off_));
    if (auto ev = glGetError()) throw opengl_error(ev);

    buf_->unbind();
}

void vertex_attr::enable()
{
    if (!created_) { create(); created_ = true; }
    glEnableVertexAttribArray(index_);
}

void vertex_attr::disable()
{
    if (created_) glDisableVertexAttribArray(index_);
}

////////////////////////////////////////////////////////////////////////////////
}
