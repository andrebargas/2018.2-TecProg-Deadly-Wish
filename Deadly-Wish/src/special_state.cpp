#include "special_state.h"

SpecialState::SpecialState()
    :CharacterState()
{
    current_state = SPECIAL_STATE;
    state_refresh_rate = 100;
}
