////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/shader.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
shader::shader(unsigned type, std::string_view src) :
    shad{ glCreateShader(type) }
{
    if (!shad) throw opengl_error(glGetError());

    const char* data = src.data();
    int size = src.size();

    glShaderSource(shad, 1, &data, &size);
    glCompileShader(shad);

    int status;
    glGetShaderiv(shad, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char data[1024];
        int size = 0;
        glGetShaderInfoLog(shad, sizeof(data), &size, data);

        throw opengl_error{ glsl_syntax_error, std::string(data, size) };
    }
}

shader::~shader() { glDeleteShader(shad); }

shader::shader(shader&& rhs) : shad{rhs.shad} { rhs.shad = 0; }

shader& shader::operator=(shader&& rhs)
{
    shader::~shader();
    shad = rhs.shad;
    rhs.shad = 0;
    return (*this);
}

fragment_shader::fragment_shader(std::string_view src) : shader{GL_FRAGMENT_SHADER, src} { }
vertex_shader::vertex_shader(std::string_view src) : shader{GL_VERTEX_SHADER, src} { }

////////////////////////////////////////////////////////////////////////////////
shader_program::shader_program() :
    pgm{ glCreateProgram() }
{
    if (!pgm) throw opengl_error(glGetError());
}

shader_program::~shader_program() { glDeleteProgram(pgm); }

shader_program::shader_program(shader_program&& rhs) : pgm{rhs.pgm} { rhs.pgm = 0; }

shader_program& shader_program::operator=(shader_program&& rhs)
{
    shader_program::~shader_program();
    pgm = rhs.pgm;
    rhs.pgm = 0;
    return (*this);
}

void shader_program::attach(const shader& s)
{
    glAttachShader(pgm, s.shad);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

void shader_program::link()
{
    glLinkProgram(pgm);
    if (auto ev = glGetError()) throw opengl_error(ev);

    int status;
    glGetProgramiv(pgm, GL_LINK_STATUS, &status);
    if (!status)
    {
        char data[1024];
        int size = 0;
        glGetProgramInfoLog(pgm, sizeof(data), &size, data);

        throw opengl_error{ glsl_link_error, std::string(data, size) };
    }
}

void shader_program::use()
{
    glUseProgram(pgm);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

////////////////////////////////////////////////////////////////////////////////
}
