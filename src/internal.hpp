#ifndef OGL_INTERNAL_HPP
#define OGL_INTERNAL_HPP

#include <ogl/error.hpp>

#include <functional>

namespace ogl
{

template<typename Fn, typename... Args>
void try_invoke(Fn&& fn, Args... args)
{
    int ev = std::invoke(std::forward<Fn>(fn), std::forward<Args>(args)...);
    if (ev) throw opengl_error{ev};
}

}

#endif
