/**\file defense_state.cpp
  *\brief This is the DefenseState class file, which is activated when
  *...some player uses defense.
  */

// Including file of class DefenseState
#include "defense_state.h"

#define STATE 100

/**\fn DefenseState ()
  *\public
  *\brief constructor method
  *does not receive parameters
  */
DefenseState::DefenseState()
    :CharacterState()
{
    // Represents the current state of the player.
    current_state = DEFENSE_STATE;
    // Time duration of a state in milliseconds.
    state_refresh_rate = STATE;
}
