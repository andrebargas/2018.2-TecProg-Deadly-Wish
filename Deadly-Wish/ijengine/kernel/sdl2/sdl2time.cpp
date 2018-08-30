#include "sdl2time.h"

SDL2Time::SDL2Time()
{
    m_time_elapsed = 0;
    m_last_update = real_time_elapsed();
    m_current_state = RUNNING;
}

unsigned
SDL2Time::real_time_elapsed() const
{
    return SDL_GetTicks();
}