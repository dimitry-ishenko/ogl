#ifndef OGL_SHADER_HPP
#define OGL_SHADER_HPP

#include <string_view>

namespace ogl
{

class shader
{
protected:
    unsigned shader_, type_;
    friend class shader_program;

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

class shader_program
{
    unsigned pgm_;

public:
    shader_program();
    ~shader_program();

    shader_program(const shader_program&) = delete;
    shader_program& operator=(const shader_program&) = delete;

    shader_program(shader_program&&);
    shader_program& operator=(shader_program&&);

    void attach(const shader&);
    void link();
    void use();
};

}

#endif
