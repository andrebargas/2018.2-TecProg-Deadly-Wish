#include "test_level.h"
#include "random_rect.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>

using namespace std;
using namespace ijengine;

TestLevel::TestLevel(int r, int g, int b, const string& next_level, const string& audio_path)
    : m_r(r), m_g(g), m_b(b), m_done(false), m_next(next_level), m_audio_path(audio_path), m_start(-1)
{
    RandomRect *rect = new RandomRect(r, g, b, 200, 200);

	//0 for windowed mode
	//1 for fullscreen mode
	//2 for fullscreen-desktop mode 
	video::set_full_screen(0);

    add_child(rect);
}

bool
TestLevel::done() const
{
    return m_done;
}

string
TestLevel::next() const
{
    return m_next;
}

string
TestLevel::audio() const
{
	return m_audio_path;
}

void
TestLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 1000)
        m_done = true;
}

void
TestLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    auto font = resources::get_font("Forelle.ttf", 60);
    canvas->set_font(font);

    canvas->clear();
    canvas->draw("Teste de fonte", 300, 200);
}

void
TestLevel::draw_self_after(Canvas *, unsigned, unsigned)
{
}
