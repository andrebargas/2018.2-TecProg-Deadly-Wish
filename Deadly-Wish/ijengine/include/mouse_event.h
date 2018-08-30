#ifndef IJENGINE_MOUSE_EVENT_H
#define IJENGINE_MOUSE_EVENT_H

#include "event.h"

#define MOUSE_EVENT_ID 0x03
#define BUTTONS_COUNT   3

#include <sstream>

using std::ostringstream;

namespace ijengine {

    class MouseEvent : public Event {
    public:
        typedef enum {PRESSED, RELEASED, MOTION} State;

        typedef
        enum { LEFT, MIDDLE, RIGHT } Button;

        MouseEvent(unsigned t, State s, State left, State middle, State right,
            int xv, int yv, int dxv, int dyv) : Event(t), m_state(s),
            m_buttons_state { left, middle, right }, m_x(xv), m_y(yv),
            m_dx(dxv), m_dy(dyv) {}

        State state() const { return m_state; }

        State button_state(Button button) const
        {
            return m_buttons_state[button];
        }

        int x() const { return m_x; }
        int y() const { return m_y; }

        int dx() const { return m_dx; }
        int dy() const { return m_dy; }

        string serialize() const 
        {
            ostringstream os;
            os << MOUSE_EVENT_ID << "," << (int) m_state << ","
                << (int) m_buttons_state[LEFT] << "," <<
                (int) m_buttons_state[MIDDLE] << "," <<
                (int) m_buttons_state[RIGHT] << "," << m_x << "," << m_y
                << m_dx << "," << m_dy;

            return os.str();
        }

    private:
        State m_state;
        State m_buttons_state[BUTTONS_COUNT];
        int m_x, m_y;
        int m_dx, m_dy;
    };
}

#endif
