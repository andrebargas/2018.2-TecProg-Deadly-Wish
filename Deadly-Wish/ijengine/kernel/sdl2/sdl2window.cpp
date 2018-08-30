#include "sdl2window.h"
#include "sdl2canvas.h"

#include <SDL2/SDL.h>


SDL2Window::SDL2Window(SDL_Window *window, SDL_Renderer *renderer) :
    m_window(window), m_renderer(renderer), m_canvas(nullptr)
{
    if (m_window)
    {
        SDL_GetWindowSize(m_window, &m_w, &m_h);
        m_canvas = new SDL2Canvas(renderer, m_w, m_h);
    }
}

SDL2Window::~SDL2Window()
{
    if (m_canvas)
        delete m_canvas;

    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);

    if (m_window)
        SDL_DestroyWindow(m_window);
}

int
SDL2Window::w() const
{
    return m_w;
}

int
SDL2Window::h() const
{
    return m_h;
}

Canvas *
SDL2Window::canvas() const
{
    return m_canvas;
}
