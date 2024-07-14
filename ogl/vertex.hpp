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
class shader_program;
class vertex_attr;
void draw(shader_program&, vertex_attr&, std::size_t from);

namespace internal
{
class vertex_buffer
{
protected:
    unsigned vbo;
    std::size_t bytes;

    vertex_buffer(const void* payload, std::size_t bytes);
    ~vertex_buffer();

    vertex_buffer(const vertex_buffer&) = delete;
    vertex_buffer& operator=(const vertex_buffer&) = delete;

    vertex_buffer(vertex_buffer&&);
    vertex_buffer& operator=(vertex_buffer&&);

    void bind();
    void unbind();

    friend class ogl::vertex_attr;
    friend void ogl::draw(shader_program&, vertex_attr&, std::size_t from);
};
}

////////////////////////////////////////////////////////////////////////////////
template<typename R, typename V>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R> && std::same_as< std::ranges::range_value_t<R>, V >;

template<typename V>
class vertex_buffer : public internal::vertex_buffer
{
public:
    using value_type = typename type_traits<V>::value_type;
    static constexpr auto stride = type_traits<V>::stride;

    using element_type = typename type_traits<V>::element_type;
    static constexpr auto element_size = type_traits<V>::element_size;

    static constexpr auto opengl_type = type_traits<V>::opengl_type;

    template<Payload<V> P>
    explicit vertex_buffer(P&& payload) : internal::vertex_buffer{ std::data(payload), std::size(payload) * stride } { }
};

template<typename R>
explicit vertex_buffer(R&&) -> vertex_buffer<std::ranges::range_value_t<R>>;

////////////////////////////////////////////////////////////////////////////////
template<typename B>
concept VertexBuffer = std::same_as<B, vertex_buffer<typename B::value_type>>;

class vertex_attr
{
    internal::vertex_buffer* buf;

    unsigned index;
    std::size_t element_size;
    unsigned element_type;
    ogl::norm norm;
    std::size_t stride;
    std::ptrdiff_t off;

    void create();

    bool created = false;
    void enable();
    void disable();

    friend void draw(shader_program&, vertex_attr&, std::size_t from);
    friend void draw(shader_program&, vertex_attr&, std::size_t from, std::size_t size);

public:
    template<VertexBuffer B>
    vertex_attr(B& buf, unsigned index, std::size_t element_size = B::element_size, std::ptrdiff_t off = 0, std::size_t stride = B::stride, ogl::norm norm = dont_norm) :
        buf{&buf}, index{index}, element_size{element_size}, element_type{B::opengl_type}, norm{norm}, stride{stride}, off{off}
    { }
    ~vertex_attr() { disable(); }

    vertex_attr(const vertex_attr&) = delete;
    vertex_attr& operator=(const vertex_attr&) = delete;

    vertex_attr(vertex_attr&&);
    vertex_attr& operator=(vertex_attr&&);
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
