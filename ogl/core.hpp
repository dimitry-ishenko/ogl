////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_CONTEXT_HPP
#define OGL_CONTEXT_HPP

#include <ogl/color.hpp>
#include <ogl/types.hpp>

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
class element_buffer;
class vertex_array;

void draw_trias(shader_program&, vertex_attr&, std::size_t from, std::size_t count);
void draw_trias(shader_program&, vertex_attr&, element_buffer&, std::size_t from, std::size_t count);

void draw_trias(shader_program&, vertex_array&, std::size_t from, std::size_t count);

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
