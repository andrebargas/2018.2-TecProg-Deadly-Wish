#ifndef IJENGINE_CANVAS_H
#define IJENGINE_CANVAS_H

#include "rectangle.h"
#include "point.h"
#include "color.h"
#include "line.h"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

namespace ijengine {

    class Font;
    class Texture;

    class Canvas {
    public:
        virtual ~Canvas() = default;

        virtual void draw(const Line& line) = 0;
        virtual void draw(const Point& point) = 0;
        virtual void draw(const Rectangle& rectangle) = 0;
        virtual void draw(const string& text, int x, int y) = 0;
        virtual void draw(const Texture *texture, int x, int y) = 0;
        virtual void draw(const Texture *texture, const Rectangle& r, int x, int y) = 0;

        virtual void update() = 0;
        virtual void clear() = 0;

        virtual void set_draw_color(const Color& c) = 0;
        virtual void set_clear_color(const Color& c) = 0;
        virtual void set_font(shared_ptr<Font> font) = 0;
    };
}

#endif
