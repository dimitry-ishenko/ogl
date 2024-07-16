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
std::size_t vertex_attr::size() const
{
    auto bytes = buf_->size() * buf_->value_size() - off_;
    // NB: stride_ can be 0 if data is packed
    auto stride = stride_ ? stride_ : (element_count_ * buf_->value_size());

    return bytes / stride + ((bytes % stride) ? 1 : 0);
}

////////////////////////////////////////////////////////////////////////////////
namespace { static constexpr unsigned no_index = -1; }

void vertex_attr_ptr::create()
{
    vertex_buffer::visitor::bind(*buf_);

    glVertexAttribPointer(index_, element_count_, element_type_, norm_, stride_, reinterpret_cast<const void*>(off_));
    if (auto ev = glGetError()) throw opengl_error(ev);

    vertex_buffer::visitor::unbind(*buf_);
}

vertex_attr_ptr::~vertex_attr_ptr() { if (index_ != no_index) disable(); }

vertex_attr_ptr::vertex_attr_ptr(vertex_attr_ptr&& rhs) : vertex_attr{std::move(rhs)} { rhs.index_ = no_index; }

vertex_attr_ptr& vertex_attr_ptr::operator=(vertex_attr_ptr&& rhs)
{
    vertex_attr_ptr::~vertex_attr_ptr();

    vertex_attr::operator=(std::move(rhs));
    rhs.index_ = no_index;

    return (*this);
}

void vertex_attr_ptr::enable() { glEnableVertexAttribArray(index_); }
void vertex_attr_ptr::disable() { glDisableVertexAttribArray(index_); }

////////////////////////////////////////////////////////////////////////////////
}
