#include "defense_state.h"

DefenseState::DefenseState()
    :CharacterState()
{
    current_state = DEFENSE_STATE;
    state_refresh_rate = 100;
}
