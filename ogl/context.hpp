#ifndef OGL_CONTEXT_HPP
#define OGL_CONTEXT_HPP

#include <ogl/color.hpp>
#include <ogl/types.hpp>

#include <string_view>

namespace ogl
{

class window;

class context
{
public:
    context();
    ~context();

    void window_hint(version);
    void reset_window_hints();

    window create_window(int width, int height, std::string_view title);

    void poll_events();
    void wait_events();

    void viewport(int x, int y, int width, int height);

    void clear_color(const color&);
    void clear();
};

}

#endif
