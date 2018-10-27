/**\file idle_state.cpp
  *\brief This is the archive of IdleState,that is activate when
  *the player is idle.
  */

#ifndef IDLE_STATE_H
#define IDLE_STATE_H

//Including the file of CharacterState class
#include "character_state.h"

/**\class IdleState idle_state.h "include/idle_state.h"
 *\brief Class used to define the state of idle to a player.
 */
class IdleState : public CharacterState {
public:
    /**\fn IdleState()
      *\public
      *\brief Constructor Method
      *\No parameters
      *Update the player status to "idle" and
      *it`s duration time is 275 miliseconds.
      */
    IdleState();
    /**\fn ~IdleState()
      *\public
      *\brief Destructor method
      */
    ~IdleState();
};

#endif
