#ifndef OGL_SHADER_HPP
#define OGL_SHADER_HPP

#include <ranges>
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

struct fragment_shader : shader { explicit fragment_shader(std::string_view src); };
struct vertex_shader : shader { explicit vertex_shader(std::string_view src); };

template<typename R>
concept Shaders = std::ranges::range<R> && std::derived_from< std::ranges::range_value_t<R>, shader >;

class shader_program
{
    unsigned pgm_;

    shader_program();
    void attach(const shader&);
    void link();

public:
    template<Shaders S>
    shader_program(const S& ss) : shader_program{ }
    {
        for(auto&& s : ss) attach(s);
        link();
    }
    ~shader_program();

    shader_program(const shader_program&) = delete;
    shader_program& operator=(const shader_program&) = delete;

    shader_program(shader_program&& rhs) : pgm_{rhs.pgm_} { rhs.pgm_ = 0; }
    shader_program& operator=(shader_program&& rhs)
    {
        shader_program::~shader_program();
        pgm_ = rhs.pgm_;
        rhs.pgm_ = 0;
        return (*this);
    }

    void use();
};

}

#endif
