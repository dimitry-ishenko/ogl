////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_SHADER_HPP
#define OGL_SHADER_HPP

#include <ogl/types.hpp> // movable

#include <cstddef>
#include <initializer_list>
#include <ranges>
#include <string_view>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
class shader : public movable
{
protected:
    unsigned shad;
    friend class shader_program;

    shader(unsigned type, std::string_view src);

public:
    ~shader();

    shader(shader&&);
    shader& operator=(shader&&);
};

struct fragment_shader : shader { explicit fragment_shader(std::string_view src); };
struct vertex_shader : shader { explicit vertex_shader(std::string_view src); };

////////////////////////////////////////////////////////////////////////////////
template<typename R>
concept Shaders = std::ranges::range<R> && std::derived_from< std::ranges::range_value_t<R>, shader >;

using shaders = std::initializer_list<shader>;

class vertex_attr;

class shader_program : public movable
{
    unsigned pgm;

    shader_program();
    void attach(const shader&);
    void link();
    void use();

    friend void draw_trias(shader_program&, vertex_attr&, std::size_t from, std::size_t size);

public:
    template<Shaders S>
    shader_program(S&& shaders) : shader_program{ }
    {
        for(auto&& shader : shaders) attach(shader);
        link();
    }
    ~shader_program();

    shader_program(shader_program&&);
    shader_program& operator=(shader_program&&);
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
