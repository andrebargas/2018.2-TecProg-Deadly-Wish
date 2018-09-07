#include "moving_state.h"

MovingState::MovingState()
    :CharacterState()
{
    current_state = MOVING_STATE;
    state_refresh_rate = 100;
}
