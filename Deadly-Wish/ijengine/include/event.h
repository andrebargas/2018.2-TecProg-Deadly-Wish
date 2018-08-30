#ifndef IJENGINE_EVENT_H
#define IJENGINE_EVENT_H

#include <string>
#include <utility>

using std::pair;
using std::string;

namespace ijengine {

    class Event {
    public:
        Event(unsigned t) : m_timestamp(t) {}
        virtual ~Event() = default;

        unsigned timestamp() const { return m_timestamp; }
        void set_timestamp(unsigned t) { m_timestamp = t; }

    private:
        unsigned m_timestamp;
    };
}

#endif
