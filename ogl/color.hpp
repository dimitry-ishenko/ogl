#ifndef OGL_COLOR_HPP
#define OGL_COLOR_HPP

#include <ogl/vec.hpp>

namespace ogl
{

struct color : Vector<float, 4>
{
    constexpr auto&& r() { return e[0]; }
    constexpr auto&& r() const { return e[0]; }

    constexpr auto&& g() { return e[1]; }
    constexpr auto&& g() const { return e[1]; }

    constexpr auto&& b() { return e[2]; }
    constexpr auto&& b() const { return e[2]; }

    constexpr auto&& a() { return e[3]; }
    constexpr auto&& a() const { return e[3]; }
};

}

#endif