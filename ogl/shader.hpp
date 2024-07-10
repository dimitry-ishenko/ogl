#ifndef OGL_SHADER_HPP
#define OGL_SHADER_HPP

#include <string_view>

namespace ogl
{

class shader
{
protected:
    unsigned id_, type_;

    explicit shader(unsigned type);
    ~shader();

    shader(const shader&) = delete;
    shader& operator=(const shader&) = delete;

    shader(shader&&);
    shader& operator=(shader&&);

public:
    void compile(std::string_view src);
};

class fragment_shader : public shader
{
public:
    fragment_shader();
    explicit fragment_shader(std::string_view src) : fragment_shader{ } { compile(src); }
};

class vertex_shader : public shader
{
public:
    vertex_shader();
    explicit vertex_shader(std::string_view src) : vertex_shader{ } { compile(src); }
};

}

#endif
