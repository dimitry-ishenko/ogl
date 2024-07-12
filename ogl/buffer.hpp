#ifndef OGL_BUFFER_HPP
#define OGL_BUFFER_HPP

#include <ranges>

namespace ogl
{

template<typename R>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R>;

class vertex_buffer
{
    unsigned vbo_;

    vertex_buffer(const void* payload, int size);

public:
    template<Payload P>
    explicit vertex_buffer(const P& payload) :
        vertex_buffer( payload.data(), payload.size() * sizeof(decltype(payload[0])) )
    { }
    ~vertex_buffer();

    vertex_buffer(const vertex_buffer&) = delete;
    vertex_buffer& operator=(const vertex_buffer&) = delete;

    vertex_buffer(vertex_buffer&& rhs) : vbo_{rhs.vbo_} { rhs.vbo_ = 0; }
    vertex_buffer& operator=(vertex_buffer&& rhs)
    {
        vertex_buffer::~vertex_buffer();
        vbo_ = rhs.vbo_;
        rhs.vbo_ = 0;
        return (*this);
    }
};

}

#endif
