#ifndef OGL_CONTEXT_HPP
#define OGL_CONTEXT_HPP

namespace ogl
{

class context
{
public:
    context();
    ~context();

    void poll_events();
    void wait_events();

    void viewport(int x, int y, int width, int height);
};

}

#endif
