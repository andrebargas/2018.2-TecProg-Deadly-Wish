/**\ file moving_state.h
  *\ brief This is the file of the MovingState class, which is activated when
  *... has a player drive input.
  */
#ifndef MOVING_STATE_H
#define MOVING_STATE_H

// Including file of class CharacterState
#include "character_state.h"

/**\class MovingState moving_state.h "include / moving_state.h"
  *\brief Class used to define the state of movement of a
  *players when it is invoked.
  */
class MovingState : public CharacterState {
public:
  /**\fn MovingState ()
    *\public
    *\brief constructor method
    *Does not receive parameters.
    *Updates the state of the player to move
    *and their respective duration time to 100 milliseconds.
    */
    MovingState();

  /**\fn ~ MovingState ()
    *\public
    *\brief destructor method
    */
    ~MovingState();
};

#endif