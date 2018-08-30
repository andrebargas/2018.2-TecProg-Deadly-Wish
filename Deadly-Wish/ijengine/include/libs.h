#ifndef LIBS_H
#define LIBS_H

#include <string>

using std::string;

namespace ijengine {

    class Lib {
    public:
        virtual ~Lib() = default;
        virtual string name() const = 0;
        virtual string version() const = 0;

        virtual void config(const string& param, const string& value) = 0;
        virtual void init() = 0;
    };

}

#endif
