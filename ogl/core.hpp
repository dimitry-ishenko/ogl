#ifndef OGL_CONTEXT_HPP
#define OGL_CONTEXT_HPP

#include <ogl/color.hpp>
#include <ogl/types.hpp>

namespace ogl
{

void window_hint(version);
void reset_window_hints();

void poll_events();
void wait_events();

void viewport(int x, int y, unsigned width, unsigned height);

void clear(const color&);

class shader_program;
class vertex_attr;

void draw(shader_program&, vertex_attr&, std::size_t from = 0);
void draw(shader_program&, vertex_attr&, std::size_t from, std::size_t size);

}

#endif
