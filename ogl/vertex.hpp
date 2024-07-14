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
}

////////////////////////////////////////////////////////////////////////////////
#endif
