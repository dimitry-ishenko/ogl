////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_RANGES_HPP
#define OGL_RANGES_HPP

#include <ranges>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

template<typename R, typename V>
concept range_of = std::ranges::range<R> && std::same_as< std::ranges::range_value_t<R>, V >;

template<typename R>
concept contiguous_sized_range = std::ranges::contiguous_range<R> && std::ranges::sized_range<R>;

template<typename R, typename V>
concept contiguous_sized_range_of = contiguous_sized_range<R> && std::same_as< std::ranges::range_value_t<R>, V >;

template<typename R>
using range_value_t = std::ranges::range_value_t<R>;

}

////////////////////////////////////////////////////////////////////////////////
#endif
