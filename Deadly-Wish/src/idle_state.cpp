#include "idle_state.h"

IdleState::IdleState()
    :CharacterState()
{
    m_current_state = IDLE_STATE;
    m_refresh_rate = 275;
}