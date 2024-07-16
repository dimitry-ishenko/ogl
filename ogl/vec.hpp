////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_VEC_HPP
#define OGL_VEC_HPP

#include <iterator>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
template<typename D, std::size_t N>
struct Vector
{
    using value_type = D;
    static constexpr auto size() { return N; }

    constexpr auto&& operator[](std::size_t n) { return e[n]; }
    constexpr auto&& operator[](std::size_t n) const { return e[n]; }

    constexpr auto begin() { return std::begin(e); }
    constexpr auto end() { return std::end(e); }

    constexpr auto begin() const { return std::begin(e); }
    constexpr auto end() const { return std::end(e); }

    constexpr auto cbegin() const { return std::cbegin(e); }
    constexpr auto cend() const { return std::cend(e); }

    constexpr auto rbegin() { return std::rbegin(e); }
    constexpr auto rend() { return std::rend(e); }

    constexpr auto crbegin() const { return std::crbegin(e); }
    constexpr auto crend() const { return std::crend(e); }

    D e[N];
};

////////////////////////////////////////////////////////////////////////////////
using vec2 = Vector<float, 2>;
using vec3 = Vector<float, 3>;
using vec4 = Vector<float, 4>;

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
