#include "death_state.h"

DeathState::DeathState()
    :CharacterState()
{
    current_state = DEATH_STATE;
    state_refresh_rate = 275;
}
