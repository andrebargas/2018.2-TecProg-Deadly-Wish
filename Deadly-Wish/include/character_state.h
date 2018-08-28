#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include <memory>
#include <vector>

#include "util.h"

using std::shared_ptr;
using std::vector;

using namespace ijengine;
using namespace util;

class CharacterState {
public:
    CharacterState();
    ~CharacterState();


    State current_state() const { return m_current_state; }
    unsigned refresh_rate() const { return m_refresh_rate; }

protected:
    State m_current_state;
    unsigned m_refresh_rate;

};

#endif