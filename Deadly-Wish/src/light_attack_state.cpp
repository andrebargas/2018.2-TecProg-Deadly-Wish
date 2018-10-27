/** \file light_attack_state.h
  * \brief This is the archive of LightAttackState class, that is activate when
  *  the player do a light atack
  */
 //Including file of LightAttackState
#include "light_attack_state.h"
#define LIGHT_ATTACK_STATE_DURATION 100
/**\fn LightAttackState()
  *\public
  *\brief Constructor Method
  *\No parameters
  */
LightAttackState::LightAttackState()
    :CharacterState()
{
    //Represents the actual state of the player.
    current_state = LIGHT_ATTACK_STATE;
    //Duration time in miliseconds.
    state_refresh_rate = LIGHT_ATTACK_STATE_DURATION;
}
