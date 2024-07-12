#ifndef OGL_BUFFER_HPP
#define OGL_BUFFER_HPP

#include <ranges>

namespace ogl
{

template<typename R>
concept VertexType = std::ranges::contiguous_range<R> && std::ranges::sized_range<R>;

class vertex_buffer
{
    unsigned vbo_;

    void data(const void* payload, int size);

public:
    vertex_buffer();
    ~vertex_buffer();

    template<VertexType V>
    explicit vertex_buffer(V&& payload) : vertex_buffer{ } { data(std::forward<V>(payload)); }

    vertex_buffer(const vertex_buffer&) = delete;
    vertex_buffer& operator=(const vertex_buffer&) = delete;

    vertex_buffer(vertex_buffer&&);
    vertex_buffer& operator=(vertex_buffer&&);

    template<VertexType V>
    void data(V&& payload)
    {
        data(payload.data(), payload.size() * sizeof(typename V::value_type));
    }
};

}

#endif
