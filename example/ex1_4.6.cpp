#include <ogl.hpp>

#include <exception>
#include <iostream>
#include <system_error>

int main()
try
{
    ogl::window win{ 800, 600, "Hello world" };
    win.activate();

    win.on_fb_size_changed(
        [&](int width, int height) { ogl::viewport(0, 0, width, height); }
    );

    while (!win.should_close())
    {
        if (win.key_state(ogl::key_escape) == ogl::pressed) win.should_close(true);

        ogl::clear(ogl::color{.2, .3, .3, 1});

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
