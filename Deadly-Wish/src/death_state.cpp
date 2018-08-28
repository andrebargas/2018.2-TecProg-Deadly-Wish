#include "death_state.h"

DeathState::DeathState()
    :CharacterState()
{
    m_current_state = DEATH_STATE;
    m_refresh_rate = 275;
}