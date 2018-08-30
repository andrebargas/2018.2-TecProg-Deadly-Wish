#ifndef IJENGINE_SYSTEM_EVENT_H
#define IJENGINE_SYSTEM_EVENT_H

#include "event.h"

namespace ijengine {

    class SystemEvent : public Event
    {
    public:
        typedef enum {QUIT, PAUSE} Action;

        SystemEvent(unsigned t, Action a) : Event(t), m_action(a) {}
        ~SystemEvent() {};

        Action action() const { return m_action; }

    private:
        Action m_action;
    };
}

#endif
