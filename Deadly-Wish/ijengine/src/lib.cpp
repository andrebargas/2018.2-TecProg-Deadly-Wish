#include "lib.h"
#include "exception.h"

#include <dlfcn.h>

namespace ijengine
{
    Lib::Lib(void *handle, const release_lib func)
        : m_handle(handle), m_release(func)
    {
    }

    Lib::~Lib()
    {
        if (m_handle) m_release(m_handle);
    }
        
    void *
    Lib::symbol(const string& sym) const
    {
        return m_handle ? dlsym(m_handle, sym.c_str()) : nullptr;
    }
}