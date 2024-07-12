#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/shader.hpp>

namespace ogl
{

shader::shader(unsigned type, std::string_view src) :
    shader_{ glCreateShader(type) }
{
    if (!shader_) throw opengl_error(glGetError());

    const char* data = src.data();
    int size = src.size();

    glShaderSource(shader_, 1, &data, &size);
    glCompileShader(shader_);

    int status;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char data[1024];
        int size = 0;
        glGetShaderInfoLog(shader_, sizeof(data), &size, data);

        throw opengl_error{ glsl_syntax_error, std::string(data, size) };
    }
}

shader::~shader() { glDeleteShader(shader_); }

fragment_shader::fragment_shader(std::string_view src) : shader{GL_FRAGMENT_SHADER, src} { }
vertex_shader::vertex_shader(std::string_view src) : shader{GL_VERTEX_SHADER, src} { }

shader_program::shader_program() :
    pgm_{ glCreateProgram() }
{
    if (!pgm_) throw opengl_error(glGetError());
}

shader_program::~shader_program() { glDeleteProgram(pgm_); }

shader_program::shader_program(shader_program&& rhs) :
    pgm_{rhs.pgm_}
{
    rhs.pgm_ = 0;
}

shader_program& shader_program::operator=(shader_program&& rhs)
{
    shader_program::~shader_program();

    pgm_ = rhs.pgm_;
    rhs.pgm_ = 0;

    return (*this);
}

void shader_program::attach(const shader& s)
{
    glAttachShader(pgm_, s.shader_);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

void shader_program::link()
{
    glLinkProgram(pgm_);
    if (auto ev = glGetError()) throw opengl_error(ev);

    int status;
    glGetProgramiv(pgm_, GL_LINK_STATUS, &status);
    if (!status)
    {
        char data[1024];
        int size = 0;
        glGetProgramInfoLog(pgm_, sizeof(data), &size, data);

        throw opengl_error{ glsl_link_error, std::string(data, size) };
    }
}

void shader_program::use()
{
    glUseProgram(pgm_);
    if (auto ev = glGetError()) throw opengl_error(ev);
}

}
