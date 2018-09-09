#include "time.h"

namespace ijengine
{
    unsigned
    Time::time_elapsed()
    {
        if(m_current_state == RUNNING) {
            unsigned now = real_time_elapsed();
            update_time(now);
        }
        return m_time_elapsed;
    }

    void
    Time::pause_timer()
    {
        if(m_current_state == RUNNING) {
            unsigned now = real_time_elapsed();
            update_time(now);
            m_current_state = PAUSED;
        }
    }

    void
    Time::resume_timer()
    {
        if(m_current_state == PAUSED) {
            unsigned now = real_time_elapsed();
            m_last_update = now;
            m_current_state = RUNNING;
        }
    }

    void
    Time::update_time(unsigned now) {
        m_time_elapsed += now - m_last_update;
        m_last_update = now;
    }
}
