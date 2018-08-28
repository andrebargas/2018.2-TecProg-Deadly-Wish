#include "defense_state.h"

DefenseState::DefenseState() 
    :CharacterState()
{
    m_current_state = DEFENSE_STATE;
    m_refresh_rate = 100;
}