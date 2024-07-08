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

}

#endif
