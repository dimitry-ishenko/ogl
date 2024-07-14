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
namespace internal
{
class vertex_buffer
{
protected:
    unsigned vbo_;
    std::size_t bytes_;

    vertex_buffer(const void* payload, std::size_t bytes);
    ~vertex_buffer();

    vertex_buffer(const vertex_buffer&) = delete;
    vertex_buffer& operator=(const vertex_buffer&) = delete;

    vertex_buffer(vertex_buffer&&);
    vertex_buffer& operator=(vertex_buffer&&);

    void bind();
    void unbind();

    auto bytes() const { return bytes_; }
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
    internal::vertex_buffer* buf_;

    unsigned index_;
    std::size_t element_size_;
    unsigned element_type_;
    norm norm_;
    std::size_t stride_;
    std::ptrdiff_t off_;

    void create();

    bool created_ = false;
    void enable();
    void disable();

public:
    template<VertexBuffer B>
    vertex_attr(B& buf, unsigned index, std::size_t element_size = B::element_size, std::ptrdiff_t off = 0, std::size_t stride = B::stride, ogl::norm norm = dont_norm) :
        buf_{&buf}, index_{index}, element_size_{element_size}, element_type_{B::opengl_type}, norm_{norm}, stride_{stride}, off_{off}
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
