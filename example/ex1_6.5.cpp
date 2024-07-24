#include <ogl.hpp>

#include <array>
#include <exception>
#include <iostream>
#include <system_error>
#include <vector>

using ogl::color3, ogl::vec3;

int main()
try
{
    ogl::window win{ 800, 600, "Hello world", { .ver = ogl::ver3_3 } };
    win.activate();

    win.on_fb_size_changed(
        [&](int width, int height) { ogl::viewport(0, 0, width, height); }
    );

    ogl::shader_program pgm;
    pgm.attach( ogl::vertex_shader{R"(
#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 vert_color;

void main()
{
    gl_Position = vec4(pos, 1);
    vert_color = color;
}
    )"} );
    pgm.attach( ogl::fragment_shader{R"(
#version 330 core
in vec3 vert_color;
out vec4 frag_color;

void main()
{
    frag_color = vec4(vert_color, 1);
}
    )"} );
    pgm.link();

    struct vertex
    {
        vec3 pos;
        color3 color;

        // needed for compat with vertex_buffer
        using value_type = vec3::value_type;
        static constexpr auto size() { return vec3::size() + color3::size(); }
    };

    ogl::vertex_buffer vbo{ std::vector<vertex>{
        { { -.5, -.5, 0. }, { 1, 0, 0 }, },
        { {  .5, -.5, 0. }, { 0, 1, 0 }, },
        { {  .0,  .5, 0. }, { 0, 0, 1 }, },
    }};

    ogl::vertex_array vao;
    vao.enable_attr(0, vbo, 0, 3, sizeof(vertex));
    vao.enable_attr(1, vbo, 3, 3, sizeof(vertex));

    while (!win.should_close())
    {
        if (win.key_state(ogl::key_escape) == ogl::pressed) win.should_close(true);

        ogl::clear(ogl::color4{.2, .3, .3, 1});

        ogl::draw_trias(pgm, vao, 0, vbo.size());

        win.swap_buffers();
        ogl::poll_events();
    };

    return 0;
}
catch(const std::system_error& e)
{
    std::cerr << e.code() << " - " << e.what() << std::endl;
    return 1;
}
catch(const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
