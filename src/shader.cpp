#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/shader.hpp>

namespace ogl
{

shader::shader(unsigned int type) : id_{ glCreateShader(type) } { }

shader::~shader() { glDeleteShader(id_); }

shader::shader(shader&& rhs) : id_{rhs.id_}, type_{rhs.type_} { rhs.id_ = 0; }

shader& shader::operator=(shader&& rhs)
{
    shader::~shader();
    id_ = rhs.id_;
    type_ = rhs.type_;
    rhs.id_ = 0;
    return (*this);
}

void shader::compile(std::string_view src)
{
    const char* data = src.data();
    int size = src.size();

    glShaderSource(id_, 1, &data, &size);
    glCompileShader(id_);

    int status;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char data[1024];
        int size = 0;
        glGetShaderInfoLog(id_, sizeof(data), &size, data);

        throw opengl_error{ glsl_syntax_error, std::string(data, size) };
    }
}

fragment_shader::fragment_shader() : shader{GL_FRAGMENT_SHADER} { }
vertex_shader::vertex_shader() : shader{GL_VERTEX_SHADER} { }

}
