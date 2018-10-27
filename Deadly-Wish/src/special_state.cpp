/**\file special_state.cpp
  *\brief This is the archive of SpecialState class, that is activate when
  *...a player do his special skill.
  */

//Including file of SpecialState class
#include "special_state.h"
#define SPECIAL_STATE_DURATION 100
/**\fn SpecialState()
  *\public
  \brief Constructor Method
  *\No parameters
  */
SpecialState::SpecialState()
    :CharacterState()
{
    //Update player status to "doing a special skill"
    current_state = SPECIAL_STATE;
    //Duration of the state is in miliseconds
    state_refresh_rate = SPECIAL_STATE_DURATION;
}
