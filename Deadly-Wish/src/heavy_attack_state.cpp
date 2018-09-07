#include "heavy_attack_state.h"

HeavyAttackState::HeavyAttackState()
    :CharacterState()
{
    current_state = HEAVY_ATTACK_STATE;
    state_refresh_rate = 100;
}
