#include "light_attack_state.h"

LightAttackState::LightAttackState() 
    :CharacterState()
{
    m_current_state = LIGHT_ATTACK_STATE;
    m_refresh_rate = 100;
}