#ifndef OGL_VEC_HPP
#define OGL_VEC_HPP

#include <cstdint>

namespace ogl
{

template<typename D, std::size_t N>
struct Vector
{
    constexpr auto&& operator[](std::size_t n) { return e[n]; }
    constexpr auto&& operator[](std::size_t n) const { return e[n]; }

    D e[N];
};

using vec2 = Vector<float, 2>;
using vec3 = Vector<float, 3>;
using vec4 = Vector<float, 4>;

}

#endif
