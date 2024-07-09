#ifndef OGL_BUFFER_HPP
#define OGL_BUFFER_HPP

#include <ranges>

namespace ogl
{

template<typename R>
concept BufferData = std::ranges::contiguous_range<R> && std::ranges::sized_range<R>;

class vertex_buffer
{
    unsigned int id_;

    void data(void* payload, int size);

public:
    vertex_buffer();
    ~vertex_buffer();

    template<BufferData D>
    vertex_buffer(D&& payload) : vertex_buffer{ } { data(std::forward<D>(payload)); }

    template<BufferData D>
    void data(D&& payload)
    {
        data(payload.data(), payload.size() * sizeof(typename D::value_type));
    }
};

}

#endif
