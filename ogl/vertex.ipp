////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_VERTEX_IPP
#define OGL_VERTEX_IPP

#include <ogl/vertex.hpp>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
namespace detail
{

unsigned vbo_create(const void* payload, std::size_t bytes);
void vbo_delete(unsigned);

void vbo_bind(unsigned);
void vbo_unbind();

}

////////////////////////////////////////////////////////////////////////////////
template<typename V>
template<Payload<V> R>
vertex_buffer<V>::vertex_buffer(R&& payload) : vbo_{ detail::vbo_create(std::data(payload), std::size(payload) * value_size) }, size_{ std::size(payload) } { }

template<typename V>
vertex_buffer<V>::~vertex_buffer() { detail::vbo_delete(vbo_); }

template<typename V>
vertex_buffer<V>::vertex_buffer(vertex_buffer<V>&& rhs) : vbo_{rhs.vbo_}, size_{rhs.size_} { rhs.vbo_ = 0; }

template<typename V>
vertex_buffer<V>& vertex_buffer<V>::operator=(vertex_buffer<V>&& rhs)
{
    ~vertex_buffer();
    vbo_ = rhs.vbo_;
    size_ = rhs.size_;
    rhs.vbo_ = 0;
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////
template<typename V>
vertex_attr::vertex_attr(unsigned index, vertex_buffer<V>& vbo, ogl::norm norm) :
    vertex_attr{ index, vbo.vbo_, vbo.size(), vbo.value_size, vbo.elem_size, 0, vbo.elem_count, vbo.value_size, vbo.opengl_type, norm }
{ }

template<typename V>
vertex_attr::vertex_attr(unsigned index, vertex_buffer<V>& vbo, packed_t, ogl::norm norm) :
    vertex_attr{ index, vbo.vbo_, vbo.size(), vbo.value_size, vbo.elem_size, 0, vbo.elem_count, 0, vbo.opengl_type, norm }
{ }

template<typename V>
vertex_attr::vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, ogl::norm norm) :
    vertex_attr{ index, vbo.vbo_, vbo.size(), vbo.value_size, vbo.elem_size, elem_from, elem_count, vbo.value_size, vbo.opengl_type, norm }
{ }

template<typename V>
vertex_attr::vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm norm) :
    vertex_attr{ index, vbo.vbo_, vbo.size(), vbo.value_size, vbo.elem_size, elem_from, elem_count, 0, vbo.opengl_type, norm }
{ }

template<typename V>
vertex_attr::vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm norm) :
    vertex_attr{ index, vbo.vbo_, vbo.size(), vbo.value_size, vbo.elem_size, elem_from, elem_count, stride, vbo.opengl_type, norm }
{ }

////////////////////////////////////////////////////////////////////////////////
template<typename... Args>
void vertex_array::enable_attr(Args&&... args)
{
    bind();
    ogl::vertex_attr attr{ std::forward<Args>(args)... };
    attr.enable();
    unbind();
}

template<typename V>
void vertex_array::vertex_attr(unsigned index, vertex_buffer<V>& vbo, ogl::norm norm)
{ enable_attr(index, vbo, norm); }

template<typename V>
void vertex_array::vertex_attr(unsigned index, vertex_buffer<V>& vbo, packed_t, ogl::norm norm)
{ enable_attr(index, vbo, packed, norm); }

template<typename V>
void vertex_array::vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, ogl::norm norm)
{ enable_attr(index, vbo, elem_from, elem_count, norm); }

template<typename V>
void vertex_array::vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm norm)
{ enable_attr(index, vbo, elem_from, elem_count, packed, norm); }

template<typename V>
void vertex_array::vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm norm)
{ enable_attr(index, vbo, elem_from, elem_count, stride, norm); }

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
