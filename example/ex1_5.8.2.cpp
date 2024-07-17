#include <ogl.hpp>

#include <array>
#include <exception>
#include <iostream>
#include <system_error>
#include <vector>

using ogl::vec3;

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
void main()
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1);
})"} );
    pgm.attach( ogl::fragment_shader{R"(
#version 330 core
out vec4 color;
void main()
{
    color = vec4(1, .5, .2, 1);
})"} );
    pgm.link();

    ogl::vertex_buffer vbo_1;
    vbo_1.data(std::array{
        vec3{ -.5,  .5, 0. },
        vec3{  0., -.5, 0. },
        vec3{ -1., -.5, 0. },
    });

    ogl::vertex_array vao_1;
    vao_1.vertex_attr(0, vbo_1);

    ogl::vertex_buffer vbo_2;
    vbo_2.data(std::array{
        vec3{  0.,  .5, 0. },
        vec3{  1.,  .5, 0. },
        vec3{  .5, -.5, 0. },
    });

    ogl::vertex_array vao_2;
    vao_2.vertex_attr(0, vbo_2);

    while (!win.should_close())
    {
        if (win.key_state(ogl::key_escape) == ogl::pressed) win.should_close(true);

        ogl::clear(ogl::color{.2, .3, .3, 1});
        ogl::draw_trias(pgm, vao_1, 0, vbo_1.size());
        ogl::draw_trias(pgm, vao_2, 0, vbo_2.size());

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
