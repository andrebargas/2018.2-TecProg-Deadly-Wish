/*#include "sdl2texture.h"
#include "sdl2animation.h"
#include <iostream>

#include <SDL2/SDL.h>

namespace ijengine {

    SDL2Animation::SDL2Animation(Texture *text, SDL2Animation::RenderStyle rstyle, int f_per_state, int t_states)
        : m_texture(text), render_style(rstyle), frames_per_state(f_per_state), total_states(t_states)
    {
        actual_frame = 0;
        actual_state = 0;

        if (render_style == STATE_PER_ROW)
        {
            width_per_frame = m_texture->w() / frames_per_state;
            height_per_frame = m_texture->h() / total_states;
        }
        else if (render_style == STATE_PER_COLUMN)
        {
            width_per_frame = m_texture->w() / total_states;
            height_per_frame = m_texture->h() / frames_per_state;
        }

        m_destiny = nullptr;
        m_source = new SDL_Rect { 0, 0, 0, 0 };
    }

    SDL2Animation::~SDL2Animation()
    {
        if (m_source)
            delete m_source;
    }

    void
    SDL2Animation::update()
    {
        if (actual_frame == frames_per_state-1)
            actual_frame = 0;
        else
            ++actual_frame;

        if (render_style == STATE_PER_ROW)
        {
            m_source->x = actual_frame * width_per_frame;
            m_source->y = actual_state * height_per_frame;
            m_source->h = height_per_frame;
            m_source->w = width_per_frame;
        }
        else if (render_style == STATE_PER_COLUMN)
        {
            m_source->x = actual_state * width_per_frame;
            m_source->y = actual_frame * height_per_frame;
            m_source->h = height_per_frame;
            m_source->w = width_per_frame;
        }
    }

    Canvas *
    SDL2Animation::canvas() const
    {
        return m_canvas;
    }

    Texture*
    SDL2Animation::texture() const
    {
        return m_texture;
    }

    SDL_Rect *
    SDL2Animation::source() const
    {
        return m_source;
    }

    SDL_Rect *
    SDL2Animation::destiny() const
    {
        return m_destiny;
    }

}*/
