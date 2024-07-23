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

template<typename T, std::size_t N>
consteval auto get_uniform()
{
         if constexpr (std::is_same_v<T, std::int32_t> ) return &glGetUniformiv;
    else if constexpr (std::is_same_v<T, std::uint32_t>) return &glGetUniformuiv;
    else if constexpr (std::is_same_v<T, float>        ) return &glGetUniformfv;
    else static_assert(false, "Unsupported uniform type");
}

template<typename T, std::size_t N>
consteval auto set_uniform()
{
    if constexpr (N == 1)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform1iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform1uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform1fv;
        else static_assert(false, "Unsupported uniform type");
    }
    else if constexpr (N == 2)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform2iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform2uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform2fv;
        else static_assert(false, "Unsupported uniform type");
    }
    else if constexpr (N == 3)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform3iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform3uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform3fv;
        else static_assert(false, "Unsupported uniform type");
    }
    else if constexpr (N == 4)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform4iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform4uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform4fv;
        else static_assert(false, "Unsupported uniform type");
    }
    else static_assert(false, "Unsupported uniform type");
}

}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct type_traits
{
    using value_type = std::remove_cv_t<T>;
    using elem_type  = value_type;

    static constexpr auto value_size = sizeof(value_type);
    static constexpr auto elem_size  = sizeof(elem_type);
    static constexpr auto elem_count = 1;

    static constexpr auto opengl_type = detail::opengl_type<value_type>();
    static constexpr auto get_uniform = detail::get_uniform<elem_type, elem_count>();
    static constexpr auto set_uniform = detail::set_uniform<elem_type, elem_count>();
};

////////////////////////////////////////////////////////////////////////////////
template<vector T>
struct type_traits<T>
{
    using value_type = std::remove_cv_t<T>;
    using elem_type  = typename value_type::value_type;

    static constexpr auto value_size = sizeof(value_type);
    static constexpr auto elem_size  = sizeof(elem_type);
    static constexpr auto elem_count = value_type::size();

    static constexpr auto opengl_type = type_traits<elem_type>::opengl_type;
    static constexpr auto get_uniform = detail::get_uniform<elem_type, elem_count>();
    static constexpr auto set_uniform = detail::set_uniform<elem_type, elem_count>();
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
