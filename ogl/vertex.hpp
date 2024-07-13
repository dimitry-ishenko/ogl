#ifndef OGL_BUFFER_HPP
#define OGL_BUFFER_HPP

#include <ogl/types.hpp>

#include <cstddef>
#include <initializer_list>
#include <ranges>

namespace ogl
{

template<typename R>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R>;

class vertex_buffer
{
    unsigned vbo_;

    vertex_buffer(const void* payload, int size);

    void bind();
    static void unbind();
    friend class vertex_array;

public:
    template<Payload P>
    explicit vertex_buffer(P&& payload) :
        vertex_buffer( std::data(payload), std::size(payload) * sizeof(decltype( *std::begin(payload) )) )
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

struct vertex_attr
{
    vertex_buffer& buffer;

    unsigned index;
    ogl::count count;
    ogl::type type;
    ogl::norm norm = _dont_norm;
    int stride = 0;
    std::ptrdiff_t offset = 0;
};

template<typename R>
concept VertexAttrs = std::ranges::range<R> && std::same_as< std::ranges::range_value_t<R>, vertex_attr >;

using vertex_attrs = std::initializer_list<vertex_attr>;

class vertex_array
{
    unsigned vao_;

    vertex_array();
    void enable_attr(const vertex_attr&);

public:
    template<VertexAttrs A>
    vertex_array(A&& attrs) : vertex_array{ }
    {
        bind();
        for (auto&& attr : attrs) enable_attr(attr);
        unbind();
    }

    void bind();
    static void unbind();
};

}

#endif
