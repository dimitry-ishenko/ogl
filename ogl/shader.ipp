////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_SHADER_IPP
#define OGL_SHADER_IPP

#include <ogl/shader.hpp>
#include <ogl/uniform.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
template<derived_from_shader Shader, derived_from_shader... Shaders>
void shader_program::attach(Shader&& shader, Shaders&&... shaders)
{
    attach_(std::forward<Shader>(shader));
    if constexpr (sizeof...(shaders)) attach(std::forward<Shaders>(shaders)...);
}

////////////////////////////////////////////////////////////////////////////////
template<typename V>
uniform<V> shader_program::get_uniform(std::string_view name) { return uniform<V>{ this, name }; }

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
