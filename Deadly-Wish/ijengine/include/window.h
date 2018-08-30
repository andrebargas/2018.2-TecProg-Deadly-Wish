#ifndef WINDOW_H
#define WINDOW_H

namespace ijengine {

    class Canvas;

    class Window {
    public:
        virtual ~Window() = default;

        virtual int w() const = 0;
        virtual int h() const = 0;

        virtual Canvas * canvas() const = 0;
    };
}

#endif
