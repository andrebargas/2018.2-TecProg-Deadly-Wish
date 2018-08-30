#ifndef ANIMATION_H
#define ANIMATION_H

namespace ijengine {

    class Texture;

    class Animation {
    public:
        virtual ~Animation() = default;
        virtual Texture *texture() const = 0;
        virtual Canvas * canvas() const = 0;
    };
}

#endif
