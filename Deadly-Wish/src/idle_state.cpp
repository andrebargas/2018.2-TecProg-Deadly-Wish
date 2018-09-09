#include "idle_state.h"

IdleState::IdleState()
    :CharacterState()
{
    current_state = IDLE_STATE;
    state_refresh_rate = 275;
}
