#ifndef CHARACTER_STATE_FACTORY_H
#define CHARACTER_STATE_FACTORY_H

#include "character_state.h"
#include "idle_state.h"
#include "moving_state.h"
#include "death_state.h"
#include "heavy_attack_state.h"
#include "light_attack_state.h"
#include "defense_state.h"
#include "special_state.h"
#include "util.h"

using namespace util;

class CharacterStateFactory {
public:
    CharacterStateFactory();
    ~CharacterStateFactory();


    CharacterState* change_character_state(int next_state);

protected:
    
};

#endif