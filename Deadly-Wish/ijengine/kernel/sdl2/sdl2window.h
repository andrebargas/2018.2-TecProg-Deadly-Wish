#ifndef IJENGINE_SDL2_WINDOW_H
#define IJENGINE_SDL2_WINDOW_H

#include "window.h"
#include <SDL2/SDL.h>

using namespace ijengine;

class SDL2Window : public Window {
public:
    SDL2Window(SDL_Window *window, SDL_Renderer *renderer);
    ~SDL2Window();

    int w() const;
    int h() const;

    Canvas * canvas() const;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Canvas *m_canvas;

    int m_w;
    int m_h;
};

#endif
