#include "random_rect.h"

#include <ijengine/canvas.h>
#include <cstdlib>

RandomRect::RandomRect(int r, int g, int b, int max_w, int max_h)
    : GameObject(nullptr, 100, 100),  m_r(r), m_g(g), m_b(b), m_rectangle(100, 100, rand() % max_w + 1, rand() % max_h + 1)
{
}

void
RandomRect::update_self(unsigned, unsigned)
{
    int dx = (rand() % 11) - 5;
    int dy = (rand() % 11) - 5;

    m_rectangle.set_position(m_rectangle.x() + dx, m_rectangle.y() + dy);
}

void
RandomRect::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->set_draw_color(Color(m_r, m_g, m_b));
    canvas->draw(m_rectangle);
}

void
RandomRect::draw_self_after(Canvas *, unsigned, unsigned)
{
}
