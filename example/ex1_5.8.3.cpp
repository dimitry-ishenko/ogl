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

    ogl::vertex_shader vert{R"(
#version 330 core
layout (location = 0) in vec3 pos;
void main()
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1);
})"};

    ogl::fragment_shader orange{R"(
#version 330 core
out vec4 color;
void main()
{
    color = vec4(1, .5, .2, 1);
})"};
    ogl::fragment_shader yellow{R"(
#version 330 core
out vec4 color;
void main()
{
    color = vec4(1, 1, 0, 1);
})"};

    ogl::shader_program pgm1;
    pgm1.attach(vert, orange);
    pgm1.link();

    ogl::shader_program pgm2;
    pgm2.attach(vert, yellow);
    pgm2.link();

    ogl::vertex_buffer vbo1{ std::array{
        vec3{ -.5,  .5, 0. },
        vec3{  0., -.5, 0. },
        vec3{ -1., -.5, 0. },
    } };

    ogl::vertex_array vao1;
    vao1.enable_attr(0, vbo1);

    ogl::vertex_buffer vbo2{ std::array{
        vec3{  0.,  .5, 0. },
        vec3{  1.,  .5, 0. },
        vec3{  .5, -.5, 0. },
    } };

    ogl::vertex_array vao2;
    vao2.enable_attr(0, vbo2);

    while (!win.should_close())
    {
        if (win.key_state(ogl::key_escape) == ogl::pressed) win.should_close(true);

        ogl::clear(ogl::color{.2, .3, .3, 1});
        ogl::draw_trias(pgm1, vao1, 0, vbo1.size());
        ogl::draw_trias(pgm2, vao2, 0, vbo2.size());

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
