/*#ifndef SDL2_ANIMATION_H
#define SDL2_ANIMATION_H

#include "animation.h"

namespace ijengine {

    class SDL2Animation : public Animation {
    public:
        enum RenderStyle {
            STATE_PER_ROW = 0,
            STATE_PER_COLUMN = 1,
            TOTAL = 2
        };

        SDL2Animation(Texture *tex, SDL2Animation::RenderStyle render_style, int frames_per_state, int total_states);
        ~SDL2Animation();
        int actual_state;
        Texture * texture() const;
        void update();
        Canvas * canvas() const;
        SDL_Rect * source() const;
        SDL_Rect * destiny() const;

    private:
        Texture * m_texture;
        SDL2Animation::RenderStyle render_style;
        int frames_per_state;
        int total_states;
        SDL_Rect * m_source;
        SDL_Rect * m_destiny;
        int actual_frame;
        int width_per_frame;
        int height_per_frame;
        Canvas * m_canvas;
    };
}

#endif*/
