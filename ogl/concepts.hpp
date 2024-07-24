////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_RANGES_HPP
#define OGL_RANGES_HPP

#include <concepts>
#include <ranges>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

template<typename T, typename V>
concept value_of = std::same_as<std::remove_cvref_t<T>, V>;

template<typename R>
using range_value_t = std::ranges::range_value_t<R>;

template<typename R>
concept sized_range = std::ranges::sized_range<R>;

template<typename R, typename V>
concept sized_range_of = sized_range<R> && value_of<V, range_value_t<R>>;;

template<typename R>
concept contiguous_range = std::ranges::contiguous_range<R>;

template<typename R>
concept contiguous_sized_range = contiguous_range<R> && sized_range<R>;

template<typename R, typename V>
concept contiguous_sized_range_of = contiguous_range<R> && sized_range_of<R, V>;

}

////////////////////////////////////////////////////////////////////////////////
#endif
