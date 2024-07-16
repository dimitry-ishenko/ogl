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
template<typename R>
concept Payload = std::ranges::contiguous_range<R> && std::ranges::sized_range<R>;

class vertex_buffer : public movable
{
    unsigned vbo_;
    void create(const void* payload, std::size_t bytes);

    template<typename R>
    using traits = type_traits< std::ranges::range_value_t<R> >;

    std::size_t size_; // # of values
    std::size_t value_size_;

    std::size_t element_count_; // # of elements in value
    unsigned element_type_;
    std::size_t element_size_;

    void bind();
    void unbind();

public:
    template<Payload R>
    vertex_buffer(R&& payload) : size_{ std::size(payload) }, value_size_{ traits<R>::value_size },
        element_count_{ traits<R>::element_count }, element_type_{ traits<R>::opengl_type }, element_size_{ traits<R>::element_size }
    {
        create(std::data(payload), size_ * value_size_);
    }
    ~vertex_buffer();

    vertex_buffer(vertex_buffer&&);
    vertex_buffer& operator=(vertex_buffer&&);

    auto size() const { return size_; }
    auto value_size() const { return value_size_; }

    auto element_count() const { return element_count_; }
    auto element_type() const { return element_type_; }
    auto element_size() const { return element_size_; }

    class visitor
    {
        static void bind(vertex_buffer& v) { v.bind(); }
        static void unbind(vertex_buffer& v) { v.unbind(); }
        friend class vertex_attr_ptr;
    };
};

////////////////////////////////////////////////////////////////////////////////
class vertex_attr
{
protected:
    vertex_buffer* buf_;

    unsigned index_;
    std::size_t element_count_;
    unsigned element_type_;
    ogl::norm norm_;
    std::size_t stride_;
    std::size_t off_;

public:
    explicit vertex_attr(vertex_buffer& buf, unsigned index, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, buf.element_count(), buf.element_type(), 0, buf.value_size(), norm }
    { }

    vertex_attr(vertex_buffer& buf, unsigned index, std::size_t size, std::size_t off = 0, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, size, buf.element_type(), off, buf.value_size(), norm }
    { }

    vertex_attr(vertex_buffer& buf, unsigned index, std::size_t size, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, size, buf.element_type(), off, stride, norm }
    { }

    vertex_attr(vertex_buffer& buf, unsigned index, std::size_t size, unsigned type, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        buf_{&buf}, index_{index}, element_count_{size}, element_type_{type}, norm_{norm}, stride_{stride}, off_{off}
    { }

    auto index() const { return index_; }
    auto element_count() const { return element_count_; }
    auto element_type() const { return element_type_; }
    auto norm() const { return norm_; }
    auto stride() const { return stride_; }
    auto off() const { return off_; }

    std::size_t size() const;
};

////////////////////////////////////////////////////////////////////////////////
class shader_program;

class vertex_attr_ptr : public vertex_attr
{
    void create();

    void enable();
    void disable();

public:
    explicit vertex_attr_ptr(const vertex_attr& attr) : vertex_attr{attr} { create(); }
    ~vertex_attr_ptr();

    explicit vertex_attr_ptr(vertex_buffer& buf, unsigned index, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, norm }
    { create(); }

    vertex_attr_ptr(vertex_buffer& buf, unsigned index, std::size_t size, std::size_t off = 0, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, size, off, norm }
    { create(); }

    vertex_attr_ptr(vertex_buffer& buf, unsigned index, std::size_t size, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, size, off, stride, norm }
    { create(); }

    vertex_attr_ptr(vertex_buffer& buf, unsigned index, std::size_t size, unsigned type, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_attr{ buf, index, size, type, off, stride, norm }
    { create(); }

    vertex_attr_ptr(vertex_attr_ptr&&);
    vertex_attr_ptr& operator=(vertex_attr_ptr&&);

    class visitor
    {
        static void enable(vertex_attr_ptr& v) { v.enable(); }
        static void disable(vertex_attr_ptr& v) { v.disable(); }
        friend void draw_trias(shader_program&, vertex_attr_ptr&, std::size_t, std::size_t);
    };
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
