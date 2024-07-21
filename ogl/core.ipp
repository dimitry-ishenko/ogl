////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_CORE_IPP
#define OGL_CORE_IPP

#include <ogl/core.hpp>
#include <ogl/shader.hpp>
#include <ogl/vertex.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
namespace internal
{

void draw_ebo_trias(unsigned count, unsigned type, std::size_t off);

}

////////////////////////////////////////////////////////////////////////////////
template<typename V>
void draw_trias(shader_program& pgm, vertex_attr& attr, element_buffer<V>& ebo, std::size_t from)
{
    draw_trias(pgm, attr, ebo, from, ebo.size() - from);
}

template<typename V>
void draw_trias(shader_program& pgm, vertex_attr& attr, element_buffer<V>& ebo, std::size_t from, std::size_t count)
{
    pgm.use();
    attr.enable();
    ebo.bind();

    internal::draw_ebo_trias(count, ebo.opengl_type, from * ebo.value_size);

    ebo.unbind();
    attr.disable();
}

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
