////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_VERTEX_HPP
#define OGL_VERTEX_HPP

#include <ogl/traits.hpp>
#include <ogl/types.hpp>

#include <cstddef>
#include <iterator>
#include <ranges>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
template<typename R>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R>;

class vertex_buffer : public movable
{
    unsigned vbo_;

    std::size_t value_size_, elem_size_, elem_count_;
    unsigned opengl_type_;

    std::size_t size_ = 0;

    void data(const void* payload, std::size_t bytes);
    void bind();
    void unbind();

    friend class vertex_attr;

public:
    vertex_buffer();
    ~vertex_buffer();

    vertex_buffer(vertex_buffer&&);
    vertex_buffer& operator=(vertex_buffer&&);

    template<Payload R> void data(R&& payload);
    auto size() const { return size_; }
};

////////////////////////////////////////////////////////////////////////////////
template<Payload R>
void vertex_buffer::data(R&& payload)
{
    using V = std::ranges::range_value_t<R>;
    value_size_ = type_traits<V>::value_size;
    elem_size_  = type_traits<V>::elem_size;
    elem_count_ = type_traits<V>::elem_count;
    opengl_type_= type_traits<V>::opengl_type;

    size_ = std::size(payload);
    data(std::data(payload), size_ * value_size_);
}

////////////////////////////////////////////////////////////////////////////////
class shader_program;
class element_buffer;

class vertex_attr : public movable
{
    unsigned index_;
    std::size_t size_;

    vertex_attr(unsigned index, vertex_buffer&, std::size_t elem_from, std::size_t elem_count, std::size_t stride, unsigned opengl_type, ogl::norm);

    void enable();
    void disable();

    friend class vertex_array;
    friend void draw_trias(shader_program&, vertex_attr&, std::size_t, std::size_t);
    friend void draw_trias(shader_program&, vertex_attr&, element_buffer&, std::size_t, std::size_t);

public:
    vertex_attr(unsigned index, vertex_buffer&, ogl::norm = dont_norm);
    vertex_attr(unsigned index, vertex_buffer&, packed_t, ogl::norm = dont_norm);
    vertex_attr(unsigned index, vertex_buffer&, std::size_t elem_from, std::size_t elem_count, ogl::norm = dont_norm);
    vertex_attr(unsigned index, vertex_buffer&, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm = dont_norm);
    vertex_attr(unsigned index, vertex_buffer&, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm = dont_norm);
    ~vertex_attr();

    vertex_attr(vertex_attr&&);
    vertex_attr& operator=(vertex_attr&&);

    auto size() const { return size_; }
};

////////////////////////////////////////////////////////////////////////////////
class vertex_array;

class element_buffer : public movable
{
    unsigned ebo_;

    std::size_t value_size_;
    unsigned opengl_type_;

    std::size_t size_ = 0;

    void data(const void* payload, std::size_t bytes);
    void bind();
    void unbind();

    friend class vertex_array;
    friend void draw_trias(shader_program&, vertex_attr&, element_buffer&, std::size_t, std::size_t);
    friend void draw_trias(shader_program&, vertex_array&, std::size_t, std::size_t);

public:
    element_buffer();
    ~element_buffer();

    element_buffer(element_buffer&&);
    element_buffer& operator=(element_buffer&&);

    template<Payload R> void data(R&& payload);
    auto size() const { return size_; }
};

////////////////////////////////////////////////////////////////////////////////
template<Payload R>
void element_buffer::data(R&& payload)
{
    using V = std::ranges::range_value_t<R>;
    value_size_ = type_traits<V>::value_size;
    opengl_type_= type_traits<V>::opengl_type;

    size_ = std::size(payload);
    data(std::data(payload), size_ * value_size_);
}

////////////////////////////////////////////////////////////////////////////////
class vertex_array : public movable
{
    unsigned vao_;
    ogl::element_buffer* ebo_ = nullptr;

    void bind();
    void unbind();

    friend void draw_trias(shader_program&, vertex_array&, std::size_t, std::size_t);

    template<typename... Args> void enable_attr(Args&&...);

public:
    vertex_array();
    ~vertex_array();

    vertex_array(vertex_array&&);
    vertex_array& operator=(vertex_array&&);

    void vertex_attr(unsigned index, vertex_buffer&, ogl::norm = dont_norm);
    void vertex_attr(unsigned index, vertex_buffer&, packed_t, ogl::norm = dont_norm);
    void vertex_attr(unsigned index, vertex_buffer&, std::size_t elem_from, std::size_t elem_count, ogl::norm = dont_norm);
    void vertex_attr(unsigned index, vertex_buffer&, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm = dont_norm);
    void vertex_attr(unsigned index, vertex_buffer&, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm = dont_norm);

    void element_buffer(ogl::element_buffer&);
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
