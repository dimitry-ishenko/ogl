////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_TRAITS_HPP
#define OGL_TRAITS_HPP

#include <ogl/extern.hpp>
#include <ogl/vec.hpp>

#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
namespace detail
{

template<typename T>
consteval auto opengl_type()
{
         if constexpr (std::is_same_v<T, std::int8_t>  ) return GL_BYTE;
    else if constexpr (std::is_same_v<T, std::uint8_t> ) return GL_UNSIGNED_BYTE;
    else if constexpr (std::is_same_v<T, std::int16_t> ) return GL_SHORT;
    else if constexpr (std::is_same_v<T, std::uint16_t>) return GL_UNSIGNED_SHORT;
    else if constexpr (std::is_same_v<T, std::int32_t> ) return GL_INT;
    else if constexpr (std::is_same_v<T, std::uint32_t>) return GL_UNSIGNED_INT;
    else if constexpr (std::is_same_v<T, float        >) return GL_FLOAT;
    else if constexpr (std::is_same_v<T, double       >) return GL_DOUBLE;
    else static_assert(false, "Unsupported data type");
}

}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct type_traits
{
    using value_type = std::remove_cv_t<T>;
    static constexpr std::size_t value_size = sizeof(value_type);

    using element_type = value_type;
    static constexpr std::size_t element_size = sizeof(element_type);
    static constexpr std::size_t element_count = 1;

    static constexpr auto opengl_type = detail::opengl_type<value_type>();
};

////////////////////////////////////////////////////////////////////////////////
template<typename D, std::size_t N>
struct type_traits<Vector<D, N>>
{
    using value_type = Vector<D, N>;
    static constexpr std::size_t value_size = sizeof(value_type);

    using element_type = typename value_type::value_type;
    static constexpr std::size_t element_size = sizeof(element_type);
    static constexpr std::size_t element_count = value_type::size();

    static constexpr auto opengl_type = type_traits<element_type>::opengl_type;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
