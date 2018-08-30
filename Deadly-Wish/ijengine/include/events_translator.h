#ifndef IJENGINE_EVENTS_TRANSLATOR_H
#define IJENGINE_EVENTS_TRANSLATOR_H

#include "game_event.h"

#include <map>
#include <list>
#include <string>
#include <utility>

using std::map;
using std::list;
using std::pair;
using std::string;

namespace ijengine
{
    class MouseEvent;
    class SystemEvent;
    class KeyboardEvent;
    class JoystickEvent;

    class EventsTranslator
    {
    public:
        virtual ~EventsTranslator() = default;

        virtual bool translate(GameEvent& to, const MouseEvent& from) = 0;
        virtual bool translate(GameEvent& to, const SystemEvent& from) = 0;
        virtual bool translate(GameEvent& to, const KeyboardEvent& from) = 0;
        virtual bool translate(GameEvent& to, const JoystickEvent& from) = 0;
    };
}

#endif
