////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/shader.hpp>
#include <ogl/uniform.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{
namespace internal
{

unsigned get_uniform(unsigned pgm, std::string_view name)
{
    int loc = glGetUniformLocation(pgm, name.data());
    if (auto ev = glGetError()) throw opengl_error(ev);
    if (loc < 0) throw opengl_error{glsl_no_such_variable};

    return loc;
}

}
}
