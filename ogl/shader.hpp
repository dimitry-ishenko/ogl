#ifndef OGL_SHADER_HPP
#define OGL_SHADER_HPP

#include <string_view>

namespace ogl
{

class shader
{
protected:
    unsigned shader_;
    friend class shader_program;

    shader(unsigned type, std::string_view src);

public:
    ~shader();

    shader(const shader&) = delete;
    shader& operator=(const shader&) = delete;

    shader(shader&& rhs) : shader_{rhs.shader_} { rhs.shader_ = 0; }
    shader& operator=(shader&& rhs)
    {
        shader::~shader();
        shader_ = rhs.shader_;
        rhs.shader_ = 0;
        return (*this);
    }
};

class fragment_shader : public shader { public: explicit fragment_shader(std::string_view src); };
class vertex_shader : public shader { public: explicit vertex_shader(std::string_view src); };

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
