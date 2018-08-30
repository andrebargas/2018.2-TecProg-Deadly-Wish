#ifndef IJENGINE_TEMPLATES_H
#define IJENGINE_TEMPLATES_H

#include "game_event.h"
#include "events_translator.h"

namespace ijengine
{
    namespace event
    {
        template<typename T> list<GameEvent>
        translate(list<T>& events, const list<EventsTranslator *> translators)
        {
            list<GameEvent> game_events;

            if (events.empty())
                return game_events;

            for (auto event : events)
            {
                for (const auto& translator : translators)
                {
                    GameEvent game_event;

                    if (translator->translate(game_event, event))
                        game_events.push_back(game_event);

                    if (events.empty())
                        break;
                }
            }

            return game_events;
        }
    }
}

#endif
