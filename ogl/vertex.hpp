////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_VERTEX_HPP
#define OGL_VERTEX_HPP

#include <ogl/ranges.hpp>
#include <ogl/types.hpp>

#include <cstddef>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
class shader_program;
template<typename> class element_buffer;

class vertex_attr : public movable
{
    unsigned index_;
    std::size_t size_;

    vertex_attr(unsigned index, std::size_t size, std::size_t count, unsigned type, ogl::norm, std::size_t stride, std::size_t off);

    void enable();
    void disable();

    template<typename> friend class vertex_buffer;
    friend class vertex_array;

    friend void draw_trias(shader_program&, vertex_attr&, std::size_t, std::size_t);

    template<typename U>
    friend void draw_trias(shader_program&, vertex_attr&, element_buffer<U>&, std::size_t, std::size_t);

public:
    ~vertex_attr();

    vertex_attr(vertex_attr&&);
    vertex_attr& operator=(vertex_attr&&);

    auto size() const { return size_; }
};

////////////////////////////////////////////////////////////////////////////////
template<typename V>
class buffer : public movable
{
    unsigned name_, target_;
    std::size_t size_ = 0;

protected:
    using value_type = type_traits<V>::value_type;
    using elem_type  = type_traits<V>::elem_type;

    static constexpr auto value_size = type_traits<V>::value_size;
    static constexpr auto elem_size  = type_traits<V>::elem_size;
    static constexpr auto elem_count = type_traits<V>::elem_count;

    static constexpr auto opengl_type= type_traits<V>::opengl_type;

    explicit buffer(unsigned target);
    template<contiguous_sized_range_of<V> R> buffer(unsigned target, R&& payload);

    void bind();
    void unbind();

public:
    ~buffer();

    buffer(buffer&&);
    buffer& operator=(buffer&&);

    template<contiguous_sized_range_of<V> R> void data(R&& payload);
    template<contiguous_sized_range R> void user_data(R&& payload);

    auto size() const { return size_; }
};

template<typename R>
explicit buffer(R&&) -> buffer<range_value_t<R>>;

////////////////////////////////////////////////////////////////////////////////
template<typename V>
class vertex_buffer : public buffer<V>
{
public:
    vertex_buffer();
    template<contiguous_sized_range_of<V> R> explicit vertex_buffer(R&& payload);

    vertex_attr create_attr(unsigned index, ogl::norm = dont_norm);
    vertex_attr create_attr(unsigned index, packed_t, ogl::norm = dont_norm);
    vertex_attr create_attr(unsigned index, std::size_t elem_from, std::size_t elem_count, ogl::norm = dont_norm);
    vertex_attr create_attr(unsigned index, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm = dont_norm);
    vertex_attr create_attr(unsigned index, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm = dont_norm);
};

template<typename R>
explicit vertex_buffer(R&&) -> vertex_buffer<range_value_t<R>>;

////////////////////////////////////////////////////////////////////////////////
template<typename V>
class element_buffer : public buffer<V>
{
    friend class vertex_array;

    template<typename U>
    friend void draw_trias(shader_program&, vertex_attr&, element_buffer<U>&, std::size_t, std::size_t);

public:
    element_buffer();
    template<contiguous_sized_range_of<V> R> explicit element_buffer(R&& payload);
};

template<typename R>
explicit element_buffer(R&&) -> element_buffer<range_value_t<R>>;

////////////////////////////////////////////////////////////////////////////////
class vertex_array : public movable
{
    unsigned vao_;

    struct
    {
        bool bound = false;
        unsigned opengl_type;
        std::size_t value_size;
    }
    ebo_;

    void bind();
    void unbind();

    template<typename V, typename... Args>
    void enable_attr_(unsigned index, vertex_buffer<V>&, Args&&...);

    friend void draw_trias(shader_program&, vertex_array&, std::size_t, std::size_t);

public:
    vertex_array();
    ~vertex_array();

    vertex_array(vertex_array&&);
    vertex_array& operator=(vertex_array&&);

    template<typename V>
    void enable_attr(unsigned index, vertex_buffer<V>&, ogl::norm = dont_norm);
    template<typename V>
    void enable_attr(unsigned index, vertex_buffer<V>&, packed_t, ogl::norm = dont_norm);
    template<typename V>
    void enable_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, ogl::norm = dont_norm);
    template<typename V>
    void enable_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, packed_t, ogl::norm = dont_norm);
    template<typename V>
    void enable_attr(unsigned index, vertex_buffer<V>&, std::size_t elem_from, std::size_t elem_count, std::size_t stride, ogl::norm = dont_norm);

    template<typename V>
    void set_elements(element_buffer<V>&);
};

////////////////////////////////////////////////////////////////////////////////
}

#include <ogl/vertex.ipp>

////////////////////////////////////////////////////////////////////////////////
#endif
