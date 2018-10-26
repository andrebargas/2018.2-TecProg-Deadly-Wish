/**\file heavy_attack_state.cpp
  *\brief This is the file of the HeavyAttackState class, which is activated when
  *... the player uses the strong attack state.
  */

// Including file from class HeavyAttackState
#include "heavy_attack_state.h"

#define STATE 100

/**\fn HeavyAttackState ()
  *\public
  *\brief constructor method
  *does not receive parameters
  */
HeavyAttackState::HeavyAttackState()
    :CharacterState()
{
    // Represents the current state of the player.
    current_state = HEAVY_ATTACK_STATE;
    // Time duration of a state in milliseconds.
    state_refresh_rate = STATE;
}
