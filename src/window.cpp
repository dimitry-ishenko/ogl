#include <ogl/error.hpp>
#include <ogl/extern.hpp>
#include <ogl/window.hpp>

namespace ogl
{

namespace
{

struct setup
{
    setup()
    {
        glfwSetErrorCallback([](int ev, const char*) { throw opengl_error(ev); });
        glfwInit();
    }

    ~setup() { glfwTerminate(); }
};

}

window::window(int width, int height, std::string_view title) :
    win_{ nullptr, &glfwDestroyWindow }
{
    static setup once;

    win_.reset(glfwCreateWindow(width, height, title.data(), nullptr, nullptr));
    glfwSetWindowUserPointer(win_.get(), this);
}

void window::activate()
{
    glfwMakeContextCurrent(win_.get());
    if (!glewed_)
    {
        glewExperimental = GL_TRUE;
        if (auto ev = glewInit()) throw opengl_error(ev);
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

ogl::key_state window::key_state(key k)
{
    return static_cast<ogl::key_state>(glfwGetKey(win_.get(), k));
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
