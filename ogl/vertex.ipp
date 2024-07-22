////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_VERTEX_IPP
#define OGL_VERTEX_IPP

#include <ogl/vertex.hpp>

#include <cstddef>
#include <iterator>
#include <ranges>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
namespace internal
{

unsigned create_buffer();
void delete_buffer(unsigned name);

void bind_buffer(unsigned target, unsigned name);
void unbind_buffer(unsigned target);

void buffer_data(unsigned target, const void* payload, std::size_t bytes);

extern const unsigned array_target;
extern const unsigned element_target;

}

////////////////////////////////////////////////////////////////////////////////
template<typename V>
buffer<V>::buffer(unsigned target) : name_{ internal::create_buffer() }, target_{target} { }

template<typename V>
template<contiguous_sized_range_of<V> R>
buffer<V>::buffer(unsigned target, R&& payload) : buffer{target}
{
    data(std::forward<R>(payload));
}

template<typename V>
buffer<V>::~buffer() { internal::delete_buffer(name_); }

template<typename V>
buffer<V>::buffer(buffer<V>&& rhs) : name_{rhs.name_}, target_{rhs.target_}, size_{rhs.size_}
{
    rhs.name_ = 0;
    rhs.size_ = 0;
}

template<typename V>
buffer<V>& buffer<V>::operator=(buffer<V>&& rhs)
{
    this->~buffer();
    name_ = rhs.name_;
    target_ = rhs.target_;
    size_ = rhs.size_;

    rhs.name_ = 0;
    rhs.size_ = 0;
    return (*this);
}

template<typename V>
template<contiguous_sized_range_of<V> R>
void buffer<V>::data(R&& payload) { user_data(std::forward<R>(payload)); }

template<typename V>
template<contiguous_sized_range R>
void buffer<V>::user_data(R&& payload)
{
    constexpr auto payload_value_size = sizeof(std::ranges::range_value_t<R>);
    constexpr auto ratio = payload_value_size / value_size;
    static_assert(payload_value_size % value_size == 0, "Incompatible payload type");

    bind();
    size_ = ratio * std::size(payload);
    internal::buffer_data(target_, std::data(payload), size_ * value_size);
    unbind();
}

template<typename V>
void buffer<V>::bind() { internal::bind_buffer(target_, name_); }

template<typename V>
void buffer<V>::unbind() { internal::unbind_buffer(target_); }

////////////////////////////////////////////////////////////////////////////////
template<typename V>
vertex_buffer<V>::vertex_buffer() : buffer<V>{ internal::array_target } { }

template<typename V>
template<contiguous_sized_range_of<V> R>
vertex_buffer<V>::vertex_buffer(R&& payload) : buffer<V>{ internal::array_target, std::forward<R>(payload) } { }

template<typename V>
vertex_attr vertex_buffer<V>::create_attr(unsigned index, ogl::norm norm)
{
    return create_attr(index, 0, this->elem_count, this->value_size, norm);
}

template<typename V>
vertex_attr vertex_buffer<V>::create_attr(unsigned index, packed_t, ogl::norm norm)
{
    return create_attr(index, 0, this->elem_count, 0, norm);
}

template<typename V>
vertex_attr vertex_buffer<V>::create_attr(unsigned index, std::size_t elem_from, std::size_t elem_count, ogl::norm norm)
{
    return create_attr(index, elem_from, elem_count, this->value_size, norm);
}

template<typename V>
vertex_attr vertex_buffer<V>::create_attr(unsigned index, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm norm)
{
    return create_attr(index, elem_from, elem_count, 0, norm);
}

template<typename V>
vertex_attr vertex_buffer<V>::create_attr(unsigned index, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm norm)
{
    auto off = elem_from * this->elem_size;
    if (!stride) stride = elem_count * this->value_size; // stride can be 0 to indicate packed data

    auto bytes = this->size() * this->value_size - off;
    auto attr_size = bytes / stride + ((bytes % stride) ? 1 : 0);

    this->bind();
    vertex_attr attr{ index, attr_size, elem_count, this->opengl_type, norm, stride, off };
    this->unbind();

    return attr;
}

////////////////////////////////////////////////////////////////////////////////
template<typename V>
element_buffer<V>::element_buffer() : buffer<V>{ internal::element_target } { }

template<typename V>
template<contiguous_sized_range_of<V> R>
element_buffer<V>::element_buffer(R&& payload) : buffer<V>{ internal::element_target, std::forward<R>(payload) } { }

////////////////////////////////////////////////////////////////////////////////
template<typename V, typename... Args>
void vertex_array::enable_attr_(unsigned index, vertex_buffer<V>& vbo, Args&&... args)
{
    bind();
    auto attr = vbo.create_attr(index, std::forward<Args>(args)...);
    attr.enable();
    unbind();
}

template<typename V>
void vertex_array::enable_attr(unsigned index, vertex_buffer<V>& vbo, ogl::norm norm)
{
    enable_attr_(index, vbo, norm);
}

template<typename V>
void vertex_array::enable_attr(unsigned index, vertex_buffer<V>& vbo, packed_t, ogl::norm norm)
{
    enable_attr_(index, vbo, packed, norm);
}

template<typename V>
void vertex_array::enable_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, ogl::norm norm)
{
    enable_attr_(index, vbo, elem_from, elem_count, norm);
}

template<typename V>
void vertex_array::enable_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm norm)
{
    enable_attr_(index, vbo, elem_from, elem_count, packed, norm);
}

template<typename V>
void vertex_array::enable_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm norm)
{
    enable_attr_(index, vbo, elem_from, elem_count, stride, norm);
}

template<typename V>
void vertex_array::set_elements(element_buffer<V>& ebo)
{
    bind();
    ebo.bind();
    ebo_.bound = true;
    ebo_.opengl_type = ebo.opengl_type;
    ebo_.value_size = ebo.value_size;
    unbind();
}

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
