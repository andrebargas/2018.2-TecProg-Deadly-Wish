/*\file character_state.h
  * \brief This is the CharacterState class file, which is activated when
  *... some player assumes a state in the game.
  */

#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include <memory>
#include <vector>

//! Including util.h file that contains enumerated constants 
#include "util.h"

using std::shared_ptr;
using std::vector;

using namespace ijengine;
using namespace util;

/**\class CharacterState character_state.h "include/character_state.h"
 * \brief Class used to define the state of a player in the game.
 */
class CharacterState {
public:
  /**\ fn CharacterState ()
    * \public
    * \brief constructor method
    * \does not receive parameters
    */
  CharacterState ();

  /**\fn ~CharacterState ()
    * \public
    * \brief destructor method
    * \does not receive parameters
    */
  ~CharacterState ();

  /**\fn get_current_state ()
    * \public
    * \brief get method
    * \return State returns the state of the player
    */
  State get_current_state() const { return current_state; }

  /**\fn get_refresh_rate ()
    * \ public
    * \ brief get method
    * \return unsigned returns the duration of a player state
    */
  unsigned get_refresh_rate() const { return state_refresh_rate; }

  protected:

    /*\var current_state
     * \brief Represents the current state of the player.
     */
    State current_state;

    /*\var state_refresh_rate
     * \brief Duration time of a state in milliseconds
     */
    unsigned state_refresh_rate;
};

#endif
