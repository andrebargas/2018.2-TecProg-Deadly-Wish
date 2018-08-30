#ifndef IJENGINE_SDL2_FONT_H
#define IJENGINE_SDL2_FONT_H

#include "font.h"
#include <SDL2/SDL_ttf.h>

using namespace ijengine;

class SDL2Font : public Font {
public:
    SDL2Font(const string& n, unsigned s, TTF_Font *f)
        : m_name(n), m_size(s), m_font(f)
    {
    }

    ~SDL2Font()
    {
        if (m_font)
            TTF_CloseFont(m_font);
    }

    string name() const { return m_name; }
    unsigned size() const { return m_size; }
    TTF_Font * font() const { return m_font; }

private:
    string m_name;
    unsigned m_size;
    TTF_Font *m_font;
 
};

#endif
