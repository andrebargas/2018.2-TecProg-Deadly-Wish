#ifndef IJENGINE_LIB_H
#define IJENGINE_LIB_H

#include <string>

using std::string;

namespace ijengine
{
    using release_lib = int (* const)(void *);
    
    class Lib {
    public:
        Lib(void *handle, const release_lib func);
        ~Lib();
        
        void * symbol(const string& sym) const;
        
    private:
        void *m_handle;
        release_lib m_release;
    };
}

#endif