#ifndef DEATH_STATE_H
#define DEATH_STATE_H

#include "character_state.h"

class DeathState : public CharacterState {
public:
    DeathState();
    
    ~DeathState();
};

#endif