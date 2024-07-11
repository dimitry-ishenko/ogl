#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/shader.hpp>

namespace ogl
{

shader::shader(unsigned type) :
    shader_{ glCreateShader(type) }
{
    if (!shader_) throw opengl_error(glGetError());
}

shader::~shader() { glDeleteShader(shader_); }

shader::shader(shader&& rhs) :
    shader_{rhs.shader_}, type_{rhs.type_}
{
    rhs.shader_ = 0;
}

shader& shader::operator=(shader&& rhs)
{
    shader::~shader();

    shader_ = rhs.shader_;
    type_ = rhs.type_;
    rhs.shader_ = 0;
    
    return (*this);
}

void shader::compile(std::string_view src)
{
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

fragment_shader::fragment_shader() : shader{GL_FRAGMENT_SHADER} { }
vertex_shader::vertex_shader() : shader{GL_VERTEX_SHADER} { }

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
