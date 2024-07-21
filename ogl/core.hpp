////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_CORE_HPP
#define OGL_CORE_HPP

#include <ogl/color.hpp>
#include <cstddef>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
void poll_events();
void wait_events();

void viewport(int x, int y, unsigned width, unsigned height);

void clear(const color&);

class shader_program;
class vertex_attr;
template<typename> class element_buffer;
class vertex_array;

void draw_trias(shader_program&, vertex_attr&, std::size_t from = 0);
void draw_trias(shader_program&, vertex_attr&, std::size_t from, std::size_t count);

template<typename V>
void draw_trias(shader_program&, vertex_attr&, element_buffer<V>&, std::size_t from = 0);

template<typename V>
void draw_trias(shader_program&, vertex_attr&, element_buffer<V>&, std::size_t from, std::size_t count);

void draw_trias(shader_program&, vertex_array&, std::size_t from, std::size_t count);

////////////////////////////////////////////////////////////////////////////////
}

#include <ogl/core.ipp>

////////////////////////////////////////////////////////////////////////////////
#endif
