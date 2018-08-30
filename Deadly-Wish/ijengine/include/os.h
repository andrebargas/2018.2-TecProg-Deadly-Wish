#ifndef IJENGINE_OS_H
#define IJENGINE_OS_H

#include <string>
#include <list>

using std::string;
using std::list;

namespace ijengine
{
    class Lib;
    
    namespace os
    {
        Lib * load_lib(const string& path);
        list<string> list_files(const string& dirpath);
    }
}

#endif