#ifndef IJENGINE_EVENTS_LISTENER_H
#define IJENGINE_EVENTS_LISTENER_H

namespace ijengine
{
    class GameEvent;

    class GameEventsListener
    {
    public:
        virtual ~GameEventsListener() = default;
        virtual bool on_event(const GameEvent& event) = 0;
    };
}

#endif
