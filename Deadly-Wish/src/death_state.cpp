/**\file death_state.cpp
   *\brief This is the class file of DeathState,
   *... which is activated when some player dies in the game.
   */
 
// Including file from class DeathState
#include "death_state.h"

#define STATE 275

/**\fn DeathState ()
  *\public
  *\brief constructor method
  *Does not receive parameters.
  *Updates the state of the player to dead and its respective duration time to 275 milliseconds.
  */
DeathState::DeathState ()
  :CharacterState ()
  {
    // Represents the current state of the player.
    current_state = DEATH_STATE;
    
    // Time duration of a state in milliseconds.
    state_refresh_rate = STATE;
  }
