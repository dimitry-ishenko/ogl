////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_VEC_HPP
#define OGL_VEC_HPP

#include <concepts>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
template<typename D, std::size_t N>
struct vec
{
    using value_type = D;
    static constexpr auto size() { return N; }

    constexpr auto data() { return std::data(e); }
    constexpr auto data() const { return std::data(e); }

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

template<typename V>
concept vector = std::derived_from<V, vec<typename V::value_type, V::size()>>;

////////////////////////////////////////////////////////////////////////////////
template<typename D, std::size_t N = 2>
struct vec_xy : vec<D, N>
{
    constexpr auto&& x() { return (*this)[0]; }
    constexpr auto&& x() const { return (*this)[0]; }

    constexpr auto&& y() { return (*this)[1]; }
    constexpr auto&& y() const { return (*this)[1]; }

    constexpr auto&& r() { return x(); }
    constexpr auto&& r() const { return x(); }

    constexpr auto&& g() { return y(); }
    constexpr auto&& g() const { return y(); }
};

////////////////////////////////////////////////////////////////////////////////
template<typename D, std::size_t N = 3>
struct vec_xyz : vec_xy<D, N>
{
    constexpr auto&& z() { return (*this)[2]; }
    constexpr auto&& z() const { return (*this)[2]; }

    constexpr auto&& b() { return z(); }
    constexpr auto&& b() const { return z(); }
};

////////////////////////////////////////////////////////////////////////////////
template<typename D, std::size_t N = 4>
struct vec_xyzw : vec_xyz<D, N>
{
    constexpr auto&& w() { return (*this)[3]; }
    constexpr auto&& w() const { return (*this)[3]; }

    constexpr auto&& a() { return (*this)[3]; }
    constexpr auto&& a() const { return (*this)[3]; }
};

////////////////////////////////////////////////////////////////////////////////
using vec2 = vec_xy  <float, 2>;
using vec3 = vec_xyz <float, 3>;
using vec4 = vec_xyzw<float, 4>;

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
