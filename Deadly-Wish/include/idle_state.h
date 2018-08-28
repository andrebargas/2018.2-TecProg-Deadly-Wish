#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "character_state.h"

class IdleState : public CharacterState {
public:
    IdleState();
    
    ~IdleState();
};

#endif