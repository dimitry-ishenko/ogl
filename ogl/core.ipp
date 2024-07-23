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
#include <ogl/types.hpp>
#include <ogl/vertex.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
template<typename V>
void draw_trias(shader_program& pgm, vertex_attr& attr, element_buffer<V>& ebo, std::size_t from, std::size_t count)
{
    pgm.use();
    enable_guard enable{attr};
    bind_guard bind{ebo};

    draw_elem_trias(ebo.opengl_type, count, from * ebo.value_size);
}

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
