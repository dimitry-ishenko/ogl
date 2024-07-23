////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_UNIFORM_IPP
#define OGL_UNIFORM_IPP

#include <ogl/error.hpp>
#include <ogl/shader.hpp>
#include <ogl/types.hpp>
#include <ogl/uniform.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
namespace internal
{

unsigned get_uniform(unsigned pgm, std::string_view name);

}

////////////////////////////////////////////////////////////////////////////////
template<typename V>
uniform<V>::uniform(shader_program& pgm, std::string_view name) :
    pgm_{pgm}, loc_{ internal::get_uniform(pgm_.pgm_, name) }
{ }

template<typename V>
uniform<V>& uniform<V>::operator=(const V& val)
{
    pgm_.use();

    using elem_type = type_traits<V>::elem_type;
    (*type_traits<V>::set_uniform)(loc_, 1, reinterpret_cast<const elem_type*>(&val));
    if (auto ev = glGetError()) throw opengl_error(ev);

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
