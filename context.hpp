#ifndef OGL_CONTEXT_HPP
#define OGL_CONTEXT_HPP

#include <ogl/color.hpp>

namespace ogl
{

class context
{
public:
    context();
    ~context();

    void poll_events();
    void wait_events();

    void viewport(int x, int y, int width, int height);

    void clear_color(color&&);
    void clear();
};

}

#endif
