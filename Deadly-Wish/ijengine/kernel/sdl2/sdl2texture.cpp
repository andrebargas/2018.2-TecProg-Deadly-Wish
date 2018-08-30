#include "sdl2texture.h"
#include "sdl2canvas.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace ijengine {

    SDL2Texture::SDL2Texture(SDL_Texture *t, int width, int height)
        : m_texture(t), m_w(width), m_h(height)
    {
    }

    SDL2Texture::~SDL2Texture()
    {
        if (m_texture)
            SDL_DestroyTexture(m_texture);
    }

    SDL_Texture *
    SDL2Texture::texture() const
    {
        return m_texture;
    }
}
