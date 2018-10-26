/**\file death_state.h
  *\brief This is the class file of DeathState,
  *... which is activated when some player dies in the game.
  */
 
#ifndef DEATH_STATE_H
#define DEATH_STATE_H

// Including file of class CharacterState
#include "character_state.h"

/**\class DeathState death_state.h "include / death_state.h"
  *\brief Class used to determine if a player died in the game.
  */
class DeathState : public CharacterState {
public:
    /**\fn DeathState ()
      *\public
      *\brief constructor method
      *Does not receive parameters.
      *Updates the state of the player to dead and its respective duration time to 275 milliseconds.
      */
    DeathState();
    
    /**\fn ~ DeathState ()
      *\public
      *\brief destructor method
      */
    ~DeathState();
};

#endif