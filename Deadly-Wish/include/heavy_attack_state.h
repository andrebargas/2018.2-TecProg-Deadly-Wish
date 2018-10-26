/**\file heavy_attack_state.h
  *\brief This is the file of the HeavyAttackState class, which is activated when
  *... the player uses the strong attack state.
  */

#ifndef HEAVY_ATTACK_STATE_H
#define HEAVY_ATTACK_STATE_H

// Including file of class CharacterState
#include "character_state.h"

/**\class HeavyAttackState heavy_attack_state.h "include / heavy_attack_state.h"
  *\brief Class used to define heavy attack status when any of the
  *players or invoke.
  */
class HeavyAttackState : public CharacterState {
  
public:
    /**\fn HeavyAttackState ()
      *\public
      *\brief constructor method
      *Does not receive parameters.
      *Updates the state of the player to "using heavy attack"
      *and their respective duration time to 100 milliseconds.
      */
    HeavyAttackState();
    
    /**\fn ~HeavyAttackState ()
      *\public
      *\brief destructor method
      */
    ~HeavyAttackState();
};

#endif