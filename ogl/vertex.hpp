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
        static void bind(vertex_buffer& vbo) { vbo.bind(); }
        static void unbind(vertex_buffer& vbo) { vbo.unbind(); }
        friend class vertex_attr;
    };
};

////////////////////////////////////////////////////////////////////////////////
class vertex_data
{
protected:
    unsigned index_;
    vertex_buffer* buf_;

    std::size_t element_count_;
    unsigned element_type_;
    ogl::norm norm_;
    std::size_t stride_;
    std::size_t off_;

public:
    vertex_data(unsigned index, vertex_buffer& buf, ogl::norm norm = dont_norm) :
        vertex_data{ index, buf, buf.element_count(), buf.element_type(), 0, buf.value_size(), norm }
    { }

    vertex_data(unsigned index, vertex_buffer& buf, std::size_t size, std::size_t off = 0, ogl::norm norm = dont_norm) :
        vertex_data{ index, buf, size, buf.element_type(), off, buf.value_size(), norm }
    { }

    vertex_data(unsigned index, vertex_buffer& buf, std::size_t size, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_data{ index, buf, size, buf.element_type(), off, stride, norm }
    { }

    vertex_data(unsigned index, vertex_buffer& buf, std::size_t size, unsigned type, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        index_{index}, buf_{&buf}, element_count_{size}, element_type_{type}, norm_{norm}, stride_{stride}, off_{off}
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

class vertex_attr : public vertex_data
{
    void create();

    void enable();
    void disable();

public:
    vertex_attr(const vertex_data& data) : vertex_data{data} { create(); }
    ~vertex_attr();

    vertex_attr(unsigned index, vertex_buffer& buf, ogl::norm norm = dont_norm) :
        vertex_data{ index, buf, norm }
    { create(); }

    vertex_attr(unsigned index, vertex_buffer& buf, std::size_t size, std::size_t off = 0, ogl::norm norm = dont_norm) :
        vertex_data{ index, buf, size, off, norm }
    { create(); }

    vertex_attr(unsigned index, vertex_buffer& buf, std::size_t size, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_data{ index, buf, size, off, stride, norm }
    { create(); }

    vertex_attr(unsigned index, vertex_buffer& buf, std::size_t size, unsigned type, std::size_t off, std::size_t stride, ogl::norm norm = dont_norm) :
        vertex_data{ index, buf, size, type, off, stride, norm }
    { create(); }

    vertex_attr(vertex_attr&&);
    vertex_attr& operator=(vertex_attr&&);

    class visitor
    {
        static void enable(vertex_attr& attr) { attr.enable(); }
        static void disable(vertex_attr& attr) { attr.disable(); }
        friend void draw_trias(shader_program&, vertex_attr&, std::size_t, std::size_t);
    };
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
