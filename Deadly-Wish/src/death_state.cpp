/**\file death_state.h
  *\brief This is the archive of DeathState class,
  *...that is activate when a player dies
  */

//Including the file of DeathState class
#include "death_state.h"
#define DEATH_STATE_DURATION 275

/**\fn DeathState()
  *\public
  *\brief Constructor method
  *No parameters
  *Update the player status to "dead" and
  *it`s duration time is 275 miliseconds.
  */
DeathState::DeathState()
    :CharacterState()
{
    //Update player status to "dead"
    current_state = DEATH_STATE;
    //Duration of the state is in miliseconds
    state_refresh_rate = DEATH_STATE_DURATION;
}
