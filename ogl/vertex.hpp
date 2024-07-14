#ifndef OGL_BUFFER_HPP
#define OGL_BUFFER_HPP

#include <ogl/types.hpp>

#include <cstddef>
#include <initializer_list>
#include <ranges>

namespace ogl
{

namespace detail
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

    auto bytes() const { return bytes_; }

    void bind();
    void unbind();
};
}

template<typename R, typename V>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R> && std::same_as< std::ranges::range_value_t<R>, V >;

template<typename V>
class vertex_buffer : public detail::vertex_buffer
{
public:
    using value_type = V;

    template<Payload<V> P>
    explicit vertex_buffer(P&& payload) :
        detail::vertex_buffer{ std::data(payload), std::size(payload) * sizeof(V) }
    { }

    auto size() const { return bytes() / sizeof(value_type); }
};

template<typename R>
explicit vertex_buffer(R&&) -> vertex_buffer<std::ranges::range_value_t<R>>;

}

#endif
