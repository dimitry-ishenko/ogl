////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_BUFFER_HPP
#define OGL_BUFFER_HPP

#include <ogl/traits.hpp>
#include <ogl/types.hpp>

#include <cstddef>
#include <initializer_list>
#include <ranges>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
namespace detail
{

unsigned create(const void* payload, std::size_t bytes);
void delete_(unsigned);

void bind(unsigned);
void unbind();

}

////////////////////////////////////////////////////////////////////////////////
template<typename R, typename V>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R> && std::same_as< std::ranges::range_value_t<R>, V >;

template<typename V>
class vertex_buffer : public movable
{
    unsigned vbo_;
    std::size_t size_;

    friend class vertex_attr;

public:
    using value_type = typename type_traits<V>::value_type;
    static constexpr auto value_size = type_traits<V>::value_size;
 
    using elem_type = typename type_traits<V>::elem_type;
    static constexpr auto elem_count = type_traits<V>::elem_count;

    static constexpr auto opengl_type = type_traits<V>::opengl_type;

    template<Payload<V> R>
    vertex_buffer(R&& payload) : vbo_{ detail::create(std::data(payload), std::size(payload) * value_size) }, size_{ std::size(payload) } { }
    ~vertex_buffer() { detail::delete_(vbo_); }

    vertex_buffer(vertex_buffer&& rhs) : vbo_{rhs.vbo_}, size_{rhs.size_} { rhs.vbo_ = 0; }

    vertex_buffer& operator=(vertex_buffer&& rhs)
    {
        ~vertex_buffer();

        vbo_ = rhs.vbo_;
        size_ = rhs.size_;
        rhs.vbo_ = 0;

        return (*this);
    }

    auto size() const { return size_; }
};

template<typename R>
explicit vertex_buffer(R&&) -> vertex_buffer<std::ranges::range_value_t<R>>;

////////////////////////////////////////////////////////////////////////////////
class shader_program;

class vertex_attr : public movable
{
    unsigned index_;
    std::size_t size_;

    vertex_attr(unsigned index, unsigned vbo, std::size_t vbo_size, std::size_t vbo_value_size,
        std::size_t elem_count, unsigned type, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm
    );

    void enable();
    void disable();

    friend void draw_trias(shader_program&, vertex_attr&, std::size_t, std::size_t);

public:
    template<typename V>
    vertex_attr(unsigned index, vertex_buffer<V>& vbo, ogl::norm norm = dont_norm) :
        vertex_attr{ index, vbo, vbo.elem_count, vbo.opengl_type, 0, vbo.value_size, norm }
    { }

    template<typename V>
    vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_count, std::size_t off = 0, ogl::norm norm = dont_norm) :
        vertex_attr{ index, vbo, elem_count, vbo.opengl_type, off, vbo.value_size, norm }
    { }

    template<typename V>
    vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_count, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_attr{ index, vbo, elem_count, vbo.opengl_type, off, stride, norm }
    { }

    template<typename V>
    vertex_attr(unsigned index, vertex_buffer<V>& vbo, std::size_t elem_count, unsigned type, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_attr{ index, vbo.vbo_, vbo.size(), vbo.value_size, elem_count, type, off, stride, norm }
    { }
    ~vertex_attr();

    vertex_attr(vertex_attr&&);
    vertex_attr& operator=(vertex_attr&&);

    auto size() const { return size_; }
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
