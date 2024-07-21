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

    ogl::vertex_buffer vbo { std::array{
        vec3{  .5,  .5, 0. }, // top right
        vec3{  .5, -.5, 0. }, // bottom right
        vec3{ -.5,  .5, 0. }, // top left

        vec3{  .5, -.5, 0. }, // bottom right
        vec3{ -.5, -.5, 0. }, // bottom left
        vec3{ -.5,  .5, 0. }, // top left
    } };

    ogl::vertex_array vao;
    vao.enable_attr(0, vbo);

    while (!win.should_close())
    {
        if (win.key_state(ogl::key_escape) == ogl::pressed) win.should_close(true);

        ogl::clear(ogl::color{.2, .3, .3, 1});
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
