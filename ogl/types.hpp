////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2024 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OGL_TYPES_HPP
#define OGL_TYPES_HPP

#include <ogl/extern.hpp>
#include <ogl/vec.hpp>

#include <cstdint>
#include <concepts>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
namespace ogl
{

////////////////////////////////////////////////////////////////////////////////
struct movable
{
    constexpr movable() = default;

    constexpr movable(const movable&) = delete;
    constexpr movable& operator=(const movable&) = delete;

    constexpr movable(movable&&) = default;
    constexpr movable& operator=(movable&&) = default;
};

////////////////////////////////////////////////////////////////////////////////
struct packed_t { explicit packed_t() = default; };
inline constexpr packed_t packed{ };

////////////////////////////////////////////////////////////////////////////////
template<typename C>
class auto_bind
{
    C& obj_;

public:
    auto_bind(C& obj) : obj_{obj} { obj_.bind(); }
    ~auto_bind() { obj_.unbind(); }
};

////////////////////////////////////////////////////////////////////////////////
template<typename C>
class auto_enable
{
    C& obj_;

public:
    auto_enable(C& obj) : obj_{obj} { obj_.enable(); }
    ~auto_enable() { obj_.disable(); }
};

////////////////////////////////////////////////////////////////////////////////
enum version
{
    ver3_0 = 0x000, ver3_1, ver3_2, ver3_3,
    ver4_0 = 0x100, ver4_1, ver4_2, ver4_3, ver4_4, ver4_5, ver4_6,
};

////////////////////////////////////////////////////////////////////////////////
enum norm { dont_norm = GL_FALSE, normalize = GL_TRUE };

enum type : unsigned { }; // OpenGL type

////////////////////////////////////////////////////////////////////////////////
enum key_state
{
    released          = GLFW_RELEASE,
    pressed           = GLFW_PRESS,
    repeating         = GLFW_REPEAT,
};

////////////////////////////////////////////////////////////////////////////////
enum key
{
    key_space         = GLFW_KEY_SPACE,
    key_apostrophe    = GLFW_KEY_APOSTROPHE,
    key_comma         = GLFW_KEY_COMMA,
    key_minus         = GLFW_KEY_MINUS,
    key_period        = GLFW_KEY_PERIOD,
    key_slash         = GLFW_KEY_SLASH,
    key_0             = GLFW_KEY_0,
    key_1             = GLFW_KEY_1,
    key_2             = GLFW_KEY_2,
    key_3             = GLFW_KEY_3,
    key_4             = GLFW_KEY_4,
    key_5             = GLFW_KEY_5,
    key_6             = GLFW_KEY_6,
    key_7             = GLFW_KEY_7,
    key_8             = GLFW_KEY_8,
    key_9             = GLFW_KEY_9,
    key_semicolon     = GLFW_KEY_SEMICOLON,
    key_equal         = GLFW_KEY_EQUAL,
    key_a             = GLFW_KEY_A,
    key_b             = GLFW_KEY_B,
    key_c             = GLFW_KEY_C,
    key_d             = GLFW_KEY_D,
    key_e             = GLFW_KEY_E,
    key_f             = GLFW_KEY_F,
    key_g             = GLFW_KEY_G,
    key_h             = GLFW_KEY_H,
    key_i             = GLFW_KEY_I,
    key_j             = GLFW_KEY_J,
    key_k             = GLFW_KEY_K,
    key_l             = GLFW_KEY_L,
    key_m             = GLFW_KEY_M,
    key_n             = GLFW_KEY_N,
    key_o             = GLFW_KEY_O,
    key_p             = GLFW_KEY_P,
    key_q             = GLFW_KEY_Q,
    key_r             = GLFW_KEY_R,
    key_s             = GLFW_KEY_S,
    key_t             = GLFW_KEY_T,
    key_u             = GLFW_KEY_U,
    key_v             = GLFW_KEY_V,
    key_w             = GLFW_KEY_W,
    key_x             = GLFW_KEY_X,
    key_y             = GLFW_KEY_Y,
    key_z             = GLFW_KEY_Z,
    key_left_bracket  = GLFW_KEY_LEFT_BRACKET,
    key_backslash     = GLFW_KEY_BACKSLASH,
    key_right_bracket = GLFW_KEY_RIGHT_BRACKET,
    key_grave_accent  = GLFW_KEY_GRAVE_ACCENT,
    key_world_1       = GLFW_KEY_WORLD_1,
    key_world_2       = GLFW_KEY_WORLD_2,

    key_escape        = GLFW_KEY_ESCAPE,
    key_enter         = GLFW_KEY_ENTER,
    key_tab           = GLFW_KEY_TAB,
    key_backspace     = GLFW_KEY_BACKSPACE,
    key_insert        = GLFW_KEY_INSERT,
    key_delete        = GLFW_KEY_DELETE,
    key_right         = GLFW_KEY_RIGHT,
    key_left          = GLFW_KEY_LEFT,
    key_down          = GLFW_KEY_DOWN,
    key_up            = GLFW_KEY_UP,
    key_page_up       = GLFW_KEY_PAGE_UP,
    key_page_down     = GLFW_KEY_PAGE_DOWN,
    key_home          = GLFW_KEY_HOME,
    key_end           = GLFW_KEY_END,
    key_caps_lock     = GLFW_KEY_CAPS_LOCK,
    key_scroll_lock   = GLFW_KEY_SCROLL_LOCK,
    key_num_lock      = GLFW_KEY_NUM_LOCK,
    key_print_screen  = GLFW_KEY_PRINT_SCREEN,
    key_pause         = GLFW_KEY_PAUSE,
    key_f1            = GLFW_KEY_F1,
    key_f2            = GLFW_KEY_F2,
    key_f3            = GLFW_KEY_F3,
    key_f4            = GLFW_KEY_F4,
    key_f5            = GLFW_KEY_F5,
    key_f6            = GLFW_KEY_F6,
    key_f7            = GLFW_KEY_F7,
    key_f8            = GLFW_KEY_F8,
    key_f9            = GLFW_KEY_F9,
    key_f10           = GLFW_KEY_F10,
    key_f11           = GLFW_KEY_F11,
    key_f12           = GLFW_KEY_F12,
    key_f13           = GLFW_KEY_F13,
    key_f14           = GLFW_KEY_F14,
    key_f15           = GLFW_KEY_F15,
    key_f16           = GLFW_KEY_F16,
    key_f17           = GLFW_KEY_F17,
    key_f18           = GLFW_KEY_F18,
    key_f19           = GLFW_KEY_F19,
    key_f20           = GLFW_KEY_F20,
    key_f21           = GLFW_KEY_F21,
    key_f22           = GLFW_KEY_F22,
    key_f23           = GLFW_KEY_F23,
    key_f24           = GLFW_KEY_F24,
    key_f25           = GLFW_KEY_F25,
    key_kp_0          = GLFW_KEY_KP_0,
    key_kp_1          = GLFW_KEY_KP_1,
    key_kp_2          = GLFW_KEY_KP_2,
    key_kp_3          = GLFW_KEY_KP_3,
    key_kp_4          = GLFW_KEY_KP_4,
    key_kp_5          = GLFW_KEY_KP_5,
    key_kp_6          = GLFW_KEY_KP_6,
    key_kp_7          = GLFW_KEY_KP_7,
    key_kp_8          = GLFW_KEY_KP_8,
    key_kp_9          = GLFW_KEY_KP_9,
    key_kp_decimal    = GLFW_KEY_KP_DECIMAL,
    key_kp_divide     = GLFW_KEY_KP_DIVIDE,
    key_kp_multiply   = GLFW_KEY_KP_MULTIPLY,
    key_kp_subtract   = GLFW_KEY_KP_SUBTRACT,
    key_kp_add        = GLFW_KEY_KP_ADD,
    key_kp_enter      = GLFW_KEY_KP_ENTER,
    key_kp_equal      = GLFW_KEY_KP_EQUAL,
    key_left_shift    = GLFW_KEY_LEFT_SHIFT,
    key_left_control  = GLFW_KEY_LEFT_CONTROL,
    key_left_alt      = GLFW_KEY_LEFT_ALT,
    key_left_super    = GLFW_KEY_LEFT_SUPER,
    key_right_shift   = GLFW_KEY_RIGHT_SHIFT,
    key_right_control = GLFW_KEY_RIGHT_CONTROL,
    key_right_alt     = GLFW_KEY_RIGHT_ALT,
    key_right_super   = GLFW_KEY_RIGHT_SUPER,
    key_menu          = GLFW_KEY_MENU,
};

////////////////////////////////////////////////////////////////////////////////
namespace internal
{

template<typename T>
consteval auto opengl_type()
{
         if constexpr (std::is_same_v<T, std::int8_t>  ) return static_cast<type>(GL_BYTE);
    else if constexpr (std::is_same_v<T, std::uint8_t> ) return static_cast<type>(GL_UNSIGNED_BYTE);
    else if constexpr (std::is_same_v<T, std::int16_t> ) return static_cast<type>(GL_SHORT);
    else if constexpr (std::is_same_v<T, std::uint16_t>) return static_cast<type>(GL_UNSIGNED_SHORT);
    else if constexpr (std::is_same_v<T, std::int32_t> ) return static_cast<type>(GL_INT);
    else if constexpr (std::is_same_v<T, std::uint32_t>) return static_cast<type>(GL_UNSIGNED_INT);
    else if constexpr (std::is_same_v<T, float        >) return static_cast<type>(GL_FLOAT);
    else if constexpr (std::is_same_v<T, double       >) return static_cast<type>(GL_DOUBLE);
    else static_assert(false, "Unsupported data type");
}

template<typename T, std::size_t N>
consteval auto get_uniform()
{
         if constexpr (std::is_same_v<T, std::int32_t> ) return &glGetUniformiv;
    else if constexpr (std::is_same_v<T, std::uint32_t>) return &glGetUniformuiv;
    else if constexpr (std::is_same_v<T, float>        ) return &glGetUniformfv;
    else return nullptr;
}

template<typename T, std::size_t N>
consteval auto set_uniform()
{
    if constexpr (N == 1)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform1iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform1uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform1fv;
        else return nullptr;
    }
    else if constexpr (N == 2)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform2iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform2uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform2fv;
        else return nullptr;
    }
    else if constexpr (N == 3)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform3iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform3uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform3fv;
        else return nullptr;
    }
    else if constexpr (N == 4)
    {
             if constexpr (std::is_same_v<T, std::int32_t> ) return &glUniform4iv;
        else if constexpr (std::is_same_v<T, std::uint32_t>) return &glUniform4uiv;
        else if constexpr (std::is_same_v<T, float>        ) return &glUniform4fv;
        else return nullptr;
    }
    else return nullptr;
}

}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct type_traits
{
    using value_type = std::remove_cv_t<T>;
    using elem_type  = typename value_type::value_type;

    static constexpr auto value_size = sizeof(value_type);
    static constexpr auto elem_size  = sizeof(elem_type);
    static constexpr auto elem_count = value_type::size();

    static constexpr auto opengl_type = type_traits<elem_type>::opengl_type;
    static constexpr auto get_uniform = internal::get_uniform<elem_type, elem_count>();
    static constexpr auto set_uniform = internal::set_uniform<elem_type, elem_count>();
};

template<typename T>
concept fundamental = std::integral<T> || std::floating_point<T>;

template<fundamental T>
struct type_traits<T>
{
    using value_type = std::remove_cv_t<T>;
    using elem_type  = value_type;

    static constexpr auto value_size = sizeof(value_type);
    static constexpr auto elem_size  = sizeof(elem_type);
    static constexpr auto elem_count = 1;

    static constexpr auto opengl_type = internal::opengl_type<value_type>();
    static constexpr auto get_uniform = internal::get_uniform<elem_type, elem_count>();
    static constexpr auto set_uniform = internal::set_uniform<elem_type, elem_count>();
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
