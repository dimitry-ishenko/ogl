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
#include <ranges>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

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
    using value_type = type_traits<V>::value_type;
    using elem_type  = type_traits<V>::elem_type;

    static constexpr auto value_size = type_traits<V>::value_size;
    static constexpr auto elem_size  = type_traits<V>::elem_size;
    static constexpr auto elem_count = type_traits<V>::elem_count;

    static constexpr auto opengl_type= type_traits<V>::opengl_type;

    template<Payload<V> R> vertex_buffer(R&& payload);
    ~vertex_buffer();

    vertex_buffer(vertex_buffer&&);
    vertex_buffer& operator=(vertex_buffer&&);

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

    vertex_attr(unsigned index, unsigned vbo, std::size_t vbo_size, std::size_t vbo_value_size, std::size_t vbo_elem_size,
        std::size_t elem_from, std::size_t elem_count, std::size_t stride, unsigned type, ogl::norm norm = dont_norm
    );

    void enable();
    void disable();

    friend class vertex_array;
    friend void draw_trias(shader_program&, vertex_attr&, std::size_t, std::size_t);

public:
    template<typename V> vertex_attr(unsigned index, vertex_buffer<V>&, ogl::norm = dont_norm);
    template<typename V> vertex_attr(unsigned index, vertex_buffer<V>&, packed_t, ogl::norm = dont_norm);
    template<typename V> vertex_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, ogl::norm = dont_norm);
    template<typename V> vertex_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm = dont_norm);
    template<typename V> vertex_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm = dont_norm);
    ~vertex_attr();

    vertex_attr(vertex_attr&&);
    vertex_attr& operator=(vertex_attr&&);

    auto size() const { return size_; }
};

////////////////////////////////////////////////////////////////////////////////
class vertex_array : public movable
{
    unsigned vao_;

    void bind();
    void unbind();

    friend void draw_trias(shader_program&, vertex_array&, std::size_t, std::size_t);

    template<typename... Args> void enable_attr(Args&&...);

public:
    vertex_array();
    ~vertex_array();

    vertex_array(vertex_array&&);
    vertex_array& operator=(vertex_array&&);

    template<typename V> void vertex_attr(unsigned index, vertex_buffer<V>&, ogl::norm = dont_norm);
    template<typename V> void vertex_attr(unsigned index, vertex_buffer<V>&, packed_t, ogl::norm = dont_norm);
    template<typename V> void vertex_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, ogl::norm = dont_norm);
    template<typename V> void vertex_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm = dont_norm);
    template<typename V> void vertex_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm = dont_norm);
};

////////////////////////////////////////////////////////////////////////////////
}

#include <ogl/vertex.ipp>

////////////////////////////////////////////////////////////////////////////////
#endif
