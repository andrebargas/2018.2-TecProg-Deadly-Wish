/**\file death_state.h
  *\brief This is the archive of DeathState class,
  *...that is activate when a player dies
  */

#ifndef DEATH_STATE_H
#define DEATH_STATE_H

//Including the file of CharacterState class
#include "character_state.h"

/**\class DeathState death_state.h "include/death_state.h"
 *\brief Class used to define the state of death to a player.
 */
class DeathState : public CharacterState {
public:
    /**\fn DeathState()
      *\public
      *\brief Constructor method
      *No parameters
      *Update the player status to "dead" and
      *it`s duration time is 275 miliseconds.
      */
    DeathState();

    /**\fn ~DeathState()
      *\public
      *\brief Destructor method
      */
    ~DeathState();
};

#endif
