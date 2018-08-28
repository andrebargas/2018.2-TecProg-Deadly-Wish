#include "heavy_attack_state.h"

HeavyAttackState::HeavyAttackState() 
    :CharacterState()
{
    m_current_state = HEAVY_ATTACK_STATE;
    m_refresh_rate = 100;
}