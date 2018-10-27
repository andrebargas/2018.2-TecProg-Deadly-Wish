/** \file light_attack_state.h
  * \brief This is the archive of LightAttackState class, that is activate when
  *  the player do a light atack
  */

#ifndef LIGHT_ATTACK_STATE_H
#define LIGHT_ATTACK_STATE_H

//Including file of CharacterState class
#include "character_state.h"

/**\class LightAttackState light_attack_state.h "include/light_attack_state.h"
 *\brief Class used to define the light atack state, when a player do it
 */
class LightAttackState : public CharacterState {
public:
    /**\fn LightAttackState()
      *\public
      *\brief Constructor Method
      *No parameters
      *Update player status to "doing a light atack"
      *and this state has a duration of  100 miliseconds.
      */
    LightAttackState();

    /**\fn ~LightAttackState()
      *\public
      *\brief Destructor method
      */
    ~LightAttackState();
};

#endif