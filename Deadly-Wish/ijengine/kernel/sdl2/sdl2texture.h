#ifndef SDL2_TEXTURE_H
#define SDL2_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

#include "texture.h"
#include "canvas.h"

using std::string;

namespace ijengine {

    class SDL2Texture : public Texture {
    public:
        SDL2Texture(SDL_Texture *texture, int w, int h);
        ~SDL2Texture();

        SDL_Texture * texture() const;

        int w() const { return m_w; }
        int h() const { return m_h; }

    private:
        SDL_Texture *m_texture;
        int m_w;
        int m_h;
    };
}

#endif
