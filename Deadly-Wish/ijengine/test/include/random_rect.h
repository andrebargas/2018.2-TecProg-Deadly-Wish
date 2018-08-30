#ifndef RANDOM_RECT_H
#define RANDOM_RECT_H

#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

using namespace ijengine;

class RandomRect : public GameObject {
public:
    RandomRect(int r, int g, int b, int max_w, int max_h);

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    void draw_self_after(Canvas *canvas, unsigned now, unsigned last);

private:
    int m_r, m_g, m_b;
    Rectangle m_rectangle;
};

#endif
