/**\file moving_state.cpp
  *\brief This is the file of the MovingState class, which is activated when
  *... has a player drive input.
  */

// Including MovingState class file
#include "moving_state.h"

#define STATE 100

/**\fn MovingState()
  *\public
  *\brief constructor method
  *\does not receive parameters
  */
MovingState::MovingState()
    :CharacterState()
{
    // Transforms the current state of the player into motion.
    current_state = MOVING_STATE;
    // Time duration of a state in milliseconds
    state_refresh_rate = STATE;
}

