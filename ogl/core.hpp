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

}

#endif
