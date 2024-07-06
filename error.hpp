#ifndef OGL_ERROR_HPP
#define OGL_ERROR_HPP

#include <string>
#include <system_error>

namespace ogl
{

enum errc
{
    no_error,

    invalid_state,
    invalid_value,
    invalid_operation,
    out_of_memory,
    overflow,
    underflow,
    resource_unavailable,
    runtime_error,
    platform_error,

    unknown_error = -1
};

const std::error_category& error_category();

std::error_condition make_error_condition(errc);

class opengl_error : public std::system_error
{
public:
    explicit opengl_error(int ev);
    opengl_error(int ev, const std::string& msg);
};

}

namespace std
{

template<>
struct is_error_condition_enum<ogl::errc> : std::true_type { };

}

#endif
