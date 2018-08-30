#include "os.h"
#include "lib.h"
#include "exception.h"

#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

namespace ijengine
{
    namespace os
    {
        Lib *
        load_lib(const string& path)
        {
            void *handle = dlopen(path.c_str(), RTLD_LAZY |
                RTLD_GLOBAL);
            
            if (not handle)
                throw Exception(string("os::load_lib(): ") + dlerror());
                
            return new Lib(handle, dlclose);
        }
        
        list<string>
        list_files(const string& dirpath)
        {
            list<string> files;
            
            DIR *dir = opendir(dirpath.c_str());
            
            if (not dir)
                return files;
                
            while (auto entry = readdir(dir))
            {
                if (!strcmp(entry->d_name, ".") or
                    !strcmp(entry->d_name, ".."))
                    continue;
                    
                files.push_back(entry->d_name);
            }
            
            return files;
        }
    }
}