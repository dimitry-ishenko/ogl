#include "error.hpp"
#include "window.hpp"

#include <functional> // std::invoke

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ogl
{

namespace
{

inline auto create(int width, int height, std::string_view title, const window_hints& hints)
{
    if (hints.ver)
    {
        auto x = 3 + (*hints.ver >> 0x08), y = *hints.ver & 0xff;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, x);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, y);
    }

    using p = std::unique_ptr<GLFWwindow, void (*)(GLFWwindow*)>;
    return p{ glfwCreateWindow(width, height, title.data(), nullptr, nullptr), &glfwDestroyWindow };
}

template<typename Fn, typename... Args>
void try_invoke(Fn&& fn, Args... args)
{
    int ev = std::invoke(std::forward<Fn>(fn), std::forward<Args>(args)...);
    if (ev) throw opengl_error{ev};
}

}

window::window(context&, int width, int height, std::string_view title, const window_hints& hints) :
    win_{ create(width, height, title, hints) }
{
    glfwSetWindowUserPointer(win_.get(), this);
}

void window::activate()
{
    glfwMakeContextCurrent(win_.get());
    if (!glewed_)
    {
        glewExperimental = GL_TRUE;
        try_invoke(&glewInit);
        glewed_ = true;
    }
}

bool window::should_close() const
{
    return glfwWindowShouldClose(win_.get());
}

void window::should_close(bool yes)
{
    glfwSetWindowShouldClose(win_.get(), yes ? GLFW_TRUE : GLFW_FALSE);
}

void window::swap_buffers() const
{
    glfwSwapBuffers(win_.get());
}

void window::on_fb_size_changed(fb_size_changed cb)
{
    if (cb)
    {
        fb_size_changed_cb_ = std::move(cb);
        glfwSetFramebufferSizeCallback(win_.get(), &fb_size_changed_dispatch);
    }
    else
    {
        glfwSetFramebufferSizeCallback(win_.get(), nullptr);
        fb_size_changed_cb_ = std::move(cb);
    }
}

void window::fb_size_changed_dispatch(GLFWwindow* win, int width, int height)
{
    auto p = static_cast<window*>(glfwGetWindowUserPointer(win));
    if (p) p->fb_size_changed_cb_(width, height);
}

}
