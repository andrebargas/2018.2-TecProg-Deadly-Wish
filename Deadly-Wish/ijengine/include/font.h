#ifndef IJENGINE_FONT_H
#define IJENGINE_FONT_H

#include <string>

using std::string;

namespace ijengine {

    class Font {
    public:
        virtual ~Font() {}
        
        virtual string name() const = 0;
        virtual unsigned size() const = 0;
    };
}

#endif
