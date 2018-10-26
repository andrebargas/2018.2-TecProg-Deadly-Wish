/** \file character_factory.h
  * \brief This files define the class that create the characters in the game.
  */
#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

// Include characters classes files
#include "character.h"
#include "mage.h"
#include "infiltrator.h"
#include "soldier.h"
#include "knight.h"
// Include file with the aux methods
#include "util.h"

#include <vector>
#include <string>


using std::vector;
using std::string;

using namespace util;

/** \class CharacterFactory
 *  \brief Class used to create character object in the game, that were choosen by the players for the espefic
 *   match.
 */
class CharacterFactory {
public:
  /** \fn CharacterFactory()
    * \public
    * \brief Constructor method
    */
    CharacterFactory();
    /** \fn ~CharacterFactory()
      * \public
      * \brief Destructor method
      */
    ~CharacterFactory();

    /** enum to possible characters */
    enum {
        KNIGHT,
        SOLDIER,
        MAGE,
        INFILTRATOR
    };
    /** \fn Character* make_character(int character_code, unsigned player_id, double x_pos, double y_pos)
      * \public
      * \brief Method to create a character in the game
      * \param character_code int code related to the a possible character. Must be between 0 and 3.
      * \param player_id unsigned id for players. Must be between 1 e 4.
      * \param x_position double Position in axis X of the character to be created
      * \param y_position double Position in axis Y of the character to be created
      * \return pointer to the created character
      */
    Character* make_character(int character_code, unsigned player_id, double x_position, double y_position);

protected:
    /** \enum Players
      * enum to possible players
      */
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;

    /** \fn vector<string> choose_sprite_path(int character_code, unsigned player_id)
      * \protected
      * \brief Method to choose the path to the sprite of the respective player and character.
      * \param character_code int id of the character, a enum is used
      * \param player unsigned id of the player, a enum is used
      * \return a string vector with the paths to the sprites
      */
    vector<string> choose_sprite_path(int character_code, unsigned player_id);
    /** \var vector<string> character_sprites_paths
      *  \brief Variable to save the path to the sprites
      */
    vector<string> character_sprites_paths;
};
#endif
