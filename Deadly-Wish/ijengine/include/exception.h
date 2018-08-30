#ifndef IJENGINE_EXCEPTION_H
#define IJENGINE_EXCEPTION_H

#include <string>

using std::string;

namespace ijengine
{
    class Exception {
    public:
        Exception(string&& message)
            : m_message(message) {}
        
        string what() const { return m_message; }
        
    private:
        string m_message;
    };
}

#endif