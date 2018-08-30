#ifndef IJENGINE_SDL2CANVAS_H
#define IJENGINE_SDL2CANVAS_H

#include <SDL2/SDL.h>
#include "canvas.h"

using namespace ijengine;

class SDL2Canvas : public Canvas {
public:
    SDL2Canvas(SDL_Renderer *renderer, int width, int height);

    void draw(const Line& line);
    void draw(const Point& point);
    void draw(const Rectangle& rectangle);
    void draw(const string& text, int x, int y);
    void draw(const Texture *texture, int x, int y);
    void draw(const Texture *texture, const Rectangle& section, int x, int y);

    void clear();
    void update();

    SDL_Renderer * renderer() const;

    int w() const { return m_w; }
    int h() const { return m_h; }

    void set_draw_color(const Color& color) { m_draw_color = color; }
    void set_clear_color(const Color& color) { m_clear_color = color; }
    void set_font(shared_ptr<Font> font) { m_font = font; };

private:
    SDL_Renderer *m_renderer;
    int m_w, m_h;
    Color m_draw_color, m_clear_color;
    shared_ptr<Font> m_font;
};

#endif
