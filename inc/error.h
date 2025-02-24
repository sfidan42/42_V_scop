#ifndef ERROR_H
# define ERROR_H
# include <cstdlib>
# include <iostream>

# define ASSERT(x) if (!(x)) \
    { \
        std::cerr << "Assertion failed: " << #x << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        std::abort(); \
    }
# define GLCall(x) \
    GLClearError(); \
    x; \
    ASSERT(GLLogCall());

void GLClearError(void);
bool GLLogCall(void);

#endif