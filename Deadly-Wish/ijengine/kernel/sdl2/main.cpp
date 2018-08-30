#include "sdl2kernel.h"

using namespace ijengine;

extern "C"
{
    Kernel * create_kernel();
    void destroy_kernel(Kernel *kernel);
    
    Kernel *
    create_kernel()
    {
        return new SDL2Kernel();
    }
    
    void
    destroy_kernel(Kernel *kernel)
    {
        delete kernel;
    }
}
