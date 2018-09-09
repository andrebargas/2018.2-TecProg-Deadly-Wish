#ifndef IJENGINE_JOYSTICK_EVENT_H
#define IJENGINE_JOYSTICK_EVENT_H

#include "event.h"

#define JOYSTICK_EVENT_ID 0x04

#include <sstream>

using std::ostringstream;

namespace ijengine {

    class JoystickEvent : public Event {
    public:
        typedef enum {BUTTON_PRESSED, BUTTON_RELEASED, AXIS_MOTION} State;

        typedef enum {TRIANGLE, CIRCLE, X, SQUARE, L1, R1, L2, R2,
            BUTTON_INVALID, A, B, Y, BACK, GUIDE, START, 
            LEFTSTICK, RIGHTSTICK, LEFTSHOULDER, RIGHTSHOULDER,
            DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT, BUTTON_MAX} Button;

        typedef enum {LEFTX, LEFTY, RIGHTX, RIGHTY, TRIGGERLEFT, TRIGGERRIGHT, AXIS_MAX, AXIS_INVALID} Axis;

        JoystickEvent(unsigned t, State s, Button b, Axis a, int _which, int _value) :
            Event(t), m_state(s), m_button(b), m_axis(a), m_which(_which), m_value(_value) {}

        State state() const { return m_state; }
        Button button() const { return m_button; }
        Axis axis() const { return m_axis; }
        int which() const { return m_which; }
        int value() const { return m_value; }

    private:
        State m_state;
        Button m_button;
        Axis m_axis;
        int m_which;
        int m_value;
    };
}

#endif
