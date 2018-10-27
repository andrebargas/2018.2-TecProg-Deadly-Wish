/**\file special_state.cpp
  *\brief This is the archive of SpecialState class, that is activate when
  *...a player do his special skill.
  */

#ifndef SPECIAL_STATE_H
#define SPECIAL_STATE_H

//Including file of CharacterState class
#include "character_state.h"

/**\class SpecialState special_state.h "include/special_state.h"
 *\brief Class used to define the status of doing a special state of a player
 */
class SpecialState : public CharacterState {
public:
    /**\fn SpecialState()
      *\public
      *\brief Constructor method
      *No parameters
      *Update player status to "doing a special skill"
      *it`s duration time is 100 miliseconds.
      */
    SpecialState();

    /**\fn ~SpecialState()
      *\public
      *\brief Destructor method
      */
    ~SpecialState();
};

#endif
