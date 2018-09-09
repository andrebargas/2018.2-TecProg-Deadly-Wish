#ifndef IJENGINE_GAME_EVENT_H
#define IJENGINE_GAME_EVENT_H

#include "event.h"
#include "exception.h"

#include <map>
#include <string>
#include <sstream>

using std::map;
using std::pair;
using std::string;
using std::istringstream;
using std::ostringstream;

namespace ijengine
{
    class GameEvent : public Event
    {
    public:
        GameEvent(unsigned i = 0, unsigned ts = 0) : Event(ts), m_id(i) {}

        unsigned id() const { return m_id; }

        template<typename T>
        void set_property(const string& property, const T& value)
        {
            ostringstream os;
            os << value;

            m_properties[property] = os.str();        
        }

        template<typename T>
        T get_property(const string& property) const
        {
            if (m_properties.find(property) == m_properties.end())
                throw Exception("Invalid GameEvent property" + property);

            istringstream is(m_properties.at(property));

            T value;
            is >> value;

            return value;
        }

        void set_id(int i) { m_id = i; }

        static unsigned assign_id()
        {
            static unsigned next = 1;

            return next++;
        }

        bool operator<(const GameEvent& e) const
        {
            return timestamp() < e.timestamp();
        }

    private:
        unsigned m_id;
        map<string, string> m_properties;
    };

    namespace game_event
    {
        extern const unsigned QUIT;
        extern const unsigned PAUSE;
    }
}

#endif
