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
template<typename S>
concept derived_from_shader = std::derived_from< std::remove_cvref_t<S>, shader >;

class vertex_attr;
class vertex_array;
template<typename> class element_buffer;
template<typename> class uniform;

class shader_program : public movable
{
    unsigned pgm_;

    void attach_(const shader&);
    void use();

    friend void draw_trias(shader_program&, vertex_attr&, std::size_t, std::size_t);
    friend void draw_trias(shader_program&, vertex_array&, std::size_t, std::size_t);

    template<typename V>
    friend void draw_trias(shader_program&, vertex_attr&, element_buffer<V>&, std::size_t, std::size_t);

    template<typename> friend class uniform;

public:
    shader_program();
    ~shader_program();

    shader_program(shader_program&&);
    shader_program& operator=(shader_program&&);

    template<derived_from_shader Shader, derived_from_shader... Shaders>
    void attach(Shader&&, Shaders&&...);
    void link();

    template<typename V> uniform<V> get_uniform(std::string_view name);
};

////////////////////////////////////////////////////////////////////////////////
}

#include <ogl/shader.ipp>

////////////////////////////////////////////////////////////////////////////////
#endif
