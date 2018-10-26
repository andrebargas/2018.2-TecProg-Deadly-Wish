/**\file defense_state.h
  *\brief This is the DefenseState class file, which is activated when
  *... some player uses defense.
  */
#ifndef DEFENSE_STATE_H
#define DEFENSE_STATE_H

// Including file of class CharacterState
#include "character_state.h"

/**\class DefenseState defense_state.h "include / defense_state.h"
  *\brief Class used to define the defensive state of a
  *players in the game.
  */
class DefenseState : public CharacterState {
  
public:
    /**\fn DefenseState ()
    *\public
    *\brief constructor method
    *Does not receive parameters.
    *Updates the state of the player to "using defense"
    *and their respective duration time to 100 milliseconds.
    */
   DefenseState ();

    /**\fn ~ DefenseState ()
    *\public
    *\brief destructor method
    */
   ~DefenseState ();
};

#endif