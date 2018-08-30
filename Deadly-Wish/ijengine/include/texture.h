#ifndef TEXTURE_H
#define TEXTURE_H

namespace ijengine {

    class Texture {
    public:
        virtual ~Texture() = default;
        virtual int w() const = 0;
        virtual int h() const = 0;
    };
}

#endif
