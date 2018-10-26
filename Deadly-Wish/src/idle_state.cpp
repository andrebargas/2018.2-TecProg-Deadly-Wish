/**\file idle_state.cpp
  *\brief This is the IdleState class file, which is activated when
  *the player is stopped.
  */

// Including file of class IdleState
#include "idle_state.h"

#define STATE 275

/**\fn IdleState ()
  *\public
  *\brief constructor method
  *\Does not receive parameters.
  *\Updates the state of the player to idle and its duration time to 275 milliseconds.
  */
IdleState::IdleState ()
  :CharacterState ()
{
  // Transforms the state of the player to stop.
  current_state = IDLE_STATE;
  // Time duration of a state in milliseconds.
  state_refresh_rate = 275;
}
