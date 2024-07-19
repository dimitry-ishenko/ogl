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
    ogl::window win{ 800, 600, "Hello world", { .ver = ogl::ver3_0 } };
    win.activate();

    win.on_fb_size_changed(
        [&](int width, int height) { ogl::viewport(0, 0, width, height); }
    );

    ogl::shader_program pgm;
    pgm.attach( ogl::vertex_shader{R"(
#version 330 core
layout (location = 0) in vec3 pos;
out vec4 vcol;
void main()
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1);
    vcol = vec4(.5, 0, 0, 1);
}
    )"} );
    pgm.attach( ogl::fragment_shader{R"(
#version 330 core
in vec4 vcol;
out vec4 fcol;
void main()
{
    fcol = vcol;
}
    )"} );
    pgm.link();

    ogl::vertex_buffer vbo;
    vbo.data(std::array{
        vec3{ -.5, -.5, 0. },
        vec3{  .5, -.5, 0. },
        vec3{  .0,  .5, 0. },
    });
    ogl::vertex_attr attr{ 0, vbo };

    while (!win.should_close())
    {
        if (win.key_state(ogl::key_escape) == ogl::pressed) win.should_close(true);

        ogl::clear(ogl::color{.2, .3, .3, 1});
        ogl::draw_trias(pgm, attr, 0, attr.size());

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
