#include "moving_state.h"

MovingState::MovingState()
    :CharacterState()
{
    m_current_state = MOVING_STATE;
    m_refresh_rate = 100;
}