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


    State get_current_state() const { return current_state; }
    unsigned get_refresh_rate() const { return state_refresh_rate; }

protected:
    State current_state;
    unsigned state_refresh_rate;

};

#endif
