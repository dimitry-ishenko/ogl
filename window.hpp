#ifndef OGL_WINDOW_HPP
#define OGL_WINDOW_HPP

#include <ogl/types.hpp>

#include <functional>
#include <memory>
#include <optional>
#include <string_view>

struct GLFWwindow;

namespace ogl
{

class context;

struct window_hints
{
    std::optional<version> ver;
};

class window
{
    std::unique_ptr<GLFWwindow, void (*)(GLFWwindow*)> win_;
    bool glewed_ = false;

public:
    window(context&, int width, int height, std::string_view title, const window_hints& = { });

    void activate();

    bool should_close() const;
    void should_close(bool);

    void swap_buffers() const;

    ogl::key_state key_state(key);

    using fb_size_changed = std::function<void(int width, int height)>;
    void on_fb_size_changed(fb_size_changed);

private:
    fb_size_changed fb_size_changed_cb_;
    static void fb_size_changed_dispatch(GLFWwindow*, int width, int height);
};

}

#endif
