////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include <ogl/error.hpp>
#include <ogl/extern.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
class error_category_ : public std::error_category
{
public:
    virtual const char* name() const noexcept override { return "opengl"; }

    virtual std::string message(int ev) const override
    {
        switch (ev)
        {
        case glsl_syntax_error:             return "GLSL syntax error";
        case glsl_link_error:               return "GLSL link error";

        case GLEW_ERROR_NO_GL_VERSION:
        case GLEW_ERROR_GL_VERSION_10_ONLY:
        case GLEW_ERROR_GLX_VERSION_11_ONLY:
        case GLEW_ERROR_NO_GLX_DISPLAY:     return (const char*)(glewGetErrorString(ev));

        case GL_INVALID_ENUM:
        case GL_INVALID_VALUE:
        case GL_INVALID_OPERATION:
        case GL_STACK_OVERFLOW:
        case GL_STACK_UNDERFLOW:
        case GL_OUT_OF_MEMORY:
        case GL_INVALID_FRAMEBUFFER_OPERATION:
        case GL_CONTEXT_LOST:               return (const char*)(gluErrorString(ev));

        case GLFW_NOT_INITIALIZED:          return "GLFW has not been initialized";
        case GLFW_NO_CURRENT_CONTEXT:       return "No current context for this thread";
        case GLFW_INVALID_ENUM:             return "Invalid enum value";
        case GLFW_INVALID_VALUE:            return "Invalid value";
        case GLFW_OUT_OF_MEMORY:            return "Memory allocation failed";
        case GLFW_API_UNAVAILABLE:          return "Requested API not supported";
        case GLFW_VERSION_UNAVAILABLE:      return "Requested OpenGL version not available";
        case GLFW_PLATFORM_ERROR:           return "Platform-specific error";
        case GLFW_FORMAT_UNAVAILABLE:       return "Requested format not supported";
        case GLFW_NO_WINDOW_CONTEXT:        return "Window does not have OpenGL context";

        default: return "Unknown error";
        };
    }

    virtual std::error_condition default_error_condition(int ev) const noexcept override
    {
        switch (ev)
        {
        case glsl_syntax_error:             return runtime_error;
        case glsl_link_error:               return runtime_error;

        case GLEW_ERROR_NO_GL_VERSION:      return resource_unavailable;
        case GLEW_ERROR_GL_VERSION_10_ONLY: return resource_unavailable;
        case GLEW_ERROR_GLX_VERSION_11_ONLY:return resource_unavailable;
        case GLEW_ERROR_NO_GLX_DISPLAY:     return resource_unavailable;

        case GL_INVALID_ENUM:               return invalid_value;
        case GL_INVALID_VALUE:              return invalid_value;
        case GL_INVALID_OPERATION:          return invalid_operation;
        case GL_STACK_OVERFLOW:             return overflow;
        case GL_STACK_UNDERFLOW:            return underflow;
        case GL_OUT_OF_MEMORY:              return out_of_memory;
        case GL_INVALID_FRAMEBUFFER_OPERATION: return invalid_operation;
        case GL_CONTEXT_LOST:               return runtime_error;

        case GLFW_NOT_INITIALIZED:
        case GLFW_NO_CURRENT_CONTEXT:       return invalid_state;
        case GLFW_INVALID_ENUM:             return invalid_value;
        case GLFW_INVALID_VALUE:            return invalid_value;
        case GLFW_OUT_OF_MEMORY:            return out_of_memory;
        case GLFW_API_UNAVAILABLE:          return resource_unavailable;
        case GLFW_VERSION_UNAVAILABLE:      return resource_unavailable;
        case GLFW_PLATFORM_ERROR:           return platform_error;
        case GLFW_FORMAT_UNAVAILABLE:       return resource_unavailable;
        case GLFW_NO_WINDOW_CONTEXT:        return invalid_state;

        default: return unknown_error;
        }
    }
};

const std::error_category& error_category()
{
    static error_category_ ec;
    return ec;
}

std::error_condition make_error_condition(errc ec)
{
    return std::error_condition{ ec, ogl::error_category() };
}

opengl_error::opengl_error(int ev) :
    std::system_error{ ev, ogl::error_category() }
{ }

opengl_error::opengl_error(int ev, const std::string& msg) :
    std::system_error{ ev, ogl::error_category(), msg }
{ }

////////////////////////////////////////////////////////////////////////////////
}
