#include "light_attack_state.h"

LightAttackState::LightAttackState()
    :CharacterState()
{
    current_state = LIGHT_ATTACK_STATE;
    state_refresh_rate = 100;
}
