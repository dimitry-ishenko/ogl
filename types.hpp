#ifndef OGL_TYPES_HPP
#define OGL_TYPES_HPP

namespace ogl
{

enum key_state
{
    released          =   0, // GLFW_RELEASE
    pressed           =   1, // GLFW_PRESS
    repeating         =   2, // GLFW_REPEATE
};

enum key
{
    key_space         =  32, // GLFW_KEY_SPACE
    key_apostrophe    =  39, // GLFW_KEY_APOSTROPHE
    key_comma         =  44, // GLFW_KEY_COMMA
    key_minus         =  45, // GLFW_KEY_MINUS
    key_period        =  46, // GLFW_KEY_PERIOD
    key_slash         =  47, // GLFW_KEY_SLASH
    key_0             =  48, // GLFW_KEY_0
    key_1             =  49, // GLFW_KEY_1
    key_2             =  50, // GLFW_KEY_2
    key_3             =  51, // GLFW_KEY_3
    key_4             =  52, // GLFW_KEY_4
    key_5             =  53, // GLFW_KEY_5
    key_6             =  54, // GLFW_KEY_6
    key_7             =  55, // GLFW_KEY_7
    key_8             =  56, // GLFW_KEY_8
    key_9             =  57, // GLFW_KEY_9
    key_semicolon     =  59, // GLFW_KEY_SEMICOLON
    key_equal         =  61, // GLFW_KEY_EQUAL
    key_a             =  65, // GLFW_KEY_A
    key_b             =  66, // GLFW_KEY_B
    key_c             =  67, // GLFW_KEY_C
    key_d             =  68, // GLFW_KEY_D
    key_e             =  69, // GLFW_KEY_E
    key_f             =  70, // GLFW_KEY_F
    key_g             =  71, // GLFW_KEY_G
    key_h             =  72, // GLFW_KEY_H
    key_i             =  73, // GLFW_KEY_I
    key_j             =  74, // GLFW_KEY_J
    key_k             =  75, // GLFW_KEY_K
    key_l             =  76, // GLFW_KEY_L
    key_m             =  77, // GLFW_KEY_M
    key_n             =  78, // GLFW_KEY_N
    key_o             =  79, // GLFW_KEY_O
    key_p             =  80, // GLFW_KEY_P
    key_q             =  81, // GLFW_KEY_Q
    key_r             =  82, // GLFW_KEY_R
    key_s             =  83, // GLFW_KEY_S
    key_t             =  84, // GLFW_KEY_T
    key_u             =  85, // GLFW_KEY_U
    key_v             =  86, // GLFW_KEY_V
    key_w             =  87, // GLFW_KEY_W
    key_x             =  88, // GLFW_KEY_X
    key_y             =  89, // GLFW_KEY_Y
    key_z             =  90, // GLFW_KEY_Z
    key_left_bracket  =  91, // GLFW_KEY_LEFT_BRACKET
    key_backslash     =  92, // GLFW_KEY_BACKSLASH
    key_right_bracket =  93, // GLFW_KEY_RIGHT_BRACKET
    key_grave_accent  =  96, // GLFW_KEY_GRAVE_ACCENT
    key_world_1       = 161, // GLFW_KEY_WORLD_1
    key_world_2       = 162, // GLFW_KEY_WORLD_2

    key_escape        = 256, // GLFW_KEY_ESCAPE
    key_enter         = 257, // GLFW_KEY_ENTER
    key_tab           = 258, // GLFW_KEY_TAB
    key_backspace     = 259, // GLFW_KEY_BACKSPACE
    key_insert        = 260, // GLFW_KEY_INSERT
    key_delete        = 261, // GLFW_KEY_DELETE
    key_right         = 262, // GLFW_KEY_RIGHT
    key_left          = 263, // GLFW_KEY_LEFT
    key_down          = 264, // GLFW_KEY_DOWN
    key_up            = 265, // GLFW_KEY_UP
    key_page_up       = 266, // GLFW_KEY_PAGE_UP
    key_page_down     = 267, // GLFW_KEY_PAGE_DOWN
    key_home          = 268, // GLFW_KEY_HOME
    key_end           = 269, // GLFW_KEY_END
    key_caps_lock     = 280, // GLFW_KEY_CAPS_LOCK
    key_scroll_lock   = 281, // GLFW_KEY_SCROLL_LOCK
    key_num_lock      = 282, // GLFW_KEY_NUM_LOCK
    key_print_screen  = 283, // GLFW_KEY_PRINT_SCREEN
    key_pause         = 284, // GLFW_KEY_PAUSE
    key_f1            = 290, // GLFW_KEY_F1
    key_f2            = 291, // GLFW_KEY_F2
    key_f3            = 292, // GLFW_KEY_F3
    key_f4            = 293, // GLFW_KEY_F4
    key_f5            = 294, // GLFW_KEY_F5
    key_f6            = 295, // GLFW_KEY_F6
    key_f7            = 296, // GLFW_KEY_F7
    key_f8            = 297, // GLFW_KEY_F8
    key_f9            = 298, // GLFW_KEY_F9
    key_f10           = 299, // GLFW_KEY_F10
    key_f11           = 300, // GLFW_KEY_F11
    key_f12           = 301, // GLFW_KEY_F12
    key_f13           = 302, // GLFW_KEY_F13
    key_f14           = 303, // GLFW_KEY_F14
    key_f15           = 304, // GLFW_KEY_F15
    key_f16           = 305, // GLFW_KEY_F16
    key_f17           = 306, // GLFW_KEY_F17
    key_f18           = 307, // GLFW_KEY_F18
    key_f19           = 308, // GLFW_KEY_F19
    key_f20           = 309, // GLFW_KEY_F20
    key_f21           = 310, // GLFW_KEY_F21
    key_f22           = 311, // GLFW_KEY_F22
    key_f23           = 312, // GLFW_KEY_F23
    key_f24           = 313, // GLFW_KEY_F24
    key_f25           = 314, // GLFW_KEY_F25
    key_kp_0          = 320, // GLFW_KEY_KP_0
    key_kp_1          = 321, // GLFW_KEY_KP_1
    key_kp_2          = 322, // GLFW_KEY_KP_2
    key_kp_3          = 323, // GLFW_KEY_KP_3
    key_kp_4          = 324, // GLFW_KEY_KP_4
    key_kp_5          = 325, // GLFW_KEY_KP_5
    key_kp_6          = 326, // GLFW_KEY_KP_6
    key_kp_7          = 327, // GLFW_KEY_KP_7
    key_kp_8          = 328, // GLFW_KEY_KP_8
    key_kp_9          = 329, // GLFW_KEY_KP_9
    key_kp_decimal    = 330, // GLFW_KEY_KP_DECIMAL
    key_kp_divide     = 331, // GLFW_KEY_KP_DIVIDE
    key_kp_multiply   = 332, // GLFW_KEY_KP_MULTIPLY
    key_kp_subtract   = 333, // GLFW_KEY_KP_SUBTRACT
    key_kp_add        = 334, // GLFW_KEY_KP_ADD
    key_kp_enter      = 335, // GLFW_KEY_KP_ENTER
    key_kp_equal      = 336, // GLFW_KEY_KP_EQUAL
    key_left_shift    = 340, // GLFW_KEY_LEFT_SHIFT
    key_left_control  = 341, // GLFW_KEY_LEFT_CONTROL
    key_left_alt      = 342, // GLFW_KEY_LEFT_ALT
    key_left_super    = 343, // GLFW_KEY_LEFT_SUPER
    key_right_shift   = 344, // GLFW_KEY_RIGHT_SHIFT
    key_right_control = 345, // GLFW_KEY_RIGHT_CONTROL
    key_right_alt     = 346, // GLFW_KEY_RIGHT_ALT
    key_right_super   = 347, // GLFW_KEY_RIGHT_SUPER
    key_menu          = 348, // GLFW_KEY_MENU
};

}

#endif
