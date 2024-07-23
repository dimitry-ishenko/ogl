////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_SHADER_HPP
#define OGL_SHADER_HPP

#include <ogl/types.hpp> // movable
#include <string_view>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
class shader : public movable
{
protected:
    unsigned shader_;
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
template<typename> class uniform;

class shader_program : public movable
{
    unsigned pgm_;

    template<typename> friend class uniform;

public:
    shader_program();
    ~shader_program();

    shader_program(shader_program&&);
    shader_program& operator=(shader_program&&);

    void attach(const shader&);
    void link();
    void use();
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
