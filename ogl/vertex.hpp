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
class vertex_buffer_base
{
protected:
    unsigned vbo;
    std::size_t bytes;

    vertex_buffer_base(const void* payload, std::size_t bytes);
    ~vertex_buffer_base();

    vertex_buffer_base(const vertex_buffer_base&) = delete;
    vertex_buffer_base& operator=(const vertex_buffer_base&) = delete;

    vertex_buffer_base(vertex_buffer_base&&);
    vertex_buffer_base& operator=(vertex_buffer_base&&);

    void bind();
    void unbind();
    friend class vertex_attr;
};

////////////////////////////////////////////////////////////////////////////////
template<typename R, typename V>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R> && std::same_as< std::ranges::range_value_t<R>, V >;

template<typename V>
class vertex_buffer : public vertex_buffer_base
{
public:
    using value_type = typename type_traits<V>::value_type;
    static constexpr auto stride = type_traits<V>::stride;

    using element_type = typename type_traits<V>::element_type;
    static constexpr auto element_size = type_traits<V>::element_size;

    static constexpr auto opengl_type = type_traits<V>::opengl_type;

    template<Payload<V> P>
    explicit vertex_buffer(P&& payload) : vertex_buffer_base{ std::data(payload), std::size(payload) * stride } { }
};

template<typename R>
explicit vertex_buffer(R&&) -> vertex_buffer<std::ranges::range_value_t<R>>;

////////////////////////////////////////////////////////////////////////////////
template<typename B>
concept VertexBuffer = std::same_as<B, vertex_buffer<typename B::value_type>>;

class shader_program;

class vertex_attr
{
    unsigned index;
    std::size_t size;

    vertex_attr(vertex_buffer_base&, unsigned index, std::size_t element_size, unsigned element_type, ogl::norm, std::size_t stride, std::ptrdiff_t off);

    void enable() const;
    void disable() const;

    friend class vertex_array;
    friend void draw(shader_program&, vertex_attr&, std::size_t);
    friend void draw(shader_program&, vertex_attr&, std::size_t, std::size_t);

public:
    template<VertexBuffer B>
    vertex_attr(B& buf, unsigned index, std::size_t element_size = B::element_size, std::ptrdiff_t off = 0, std::size_t stride = B::stride, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, element_size, B::opengl_type, norm, stride, off }
    {
        size = buf.bytes / (stride ? stride : (element_size * sizeof(typename B::element_type)));
    }
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
