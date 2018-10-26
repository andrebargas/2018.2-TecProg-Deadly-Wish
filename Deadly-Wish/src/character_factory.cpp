/** \file character_factory.cpp
  * \brief This file describe the class that create the charactes in the game
  */
#include "character_factory.h"

#include <assert.h>

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

// Constructor Method
CharacterFactory::CharacterFactory()
{

}

// Destructor Method
CharacterFactory::~CharacterFactory()
{

}

/** \fn Character* make_character(int character_code, unsigned player_id, double x_pos, double y_pos)
  * \public
  * \brief Method to create a character in the game
  * \param character_code int code related to the a possible character. Must be between 0 and 3.
  * \param player_id unsigned id for players. Must be between 1 e 4.
  * \param x_position double Position in axis X of the character to be created
  * \param y_position double Position in axis Y of the character to be created
  * \return pointer to the created character
  */
Character*
CharacterFactory::make_character(int character_code, unsigned player_id, double x_position,
                                 double y_position)
{
    character_sprites_paths = choose_sprite_path(character_code, player_id);

    //Asserts to validate data
    assert(character_code >= 0);
    assert(character_code < 4);
    assert(player_id < 4);
    assert(player_id >= 0);
    assert(x_position >= 0);
    assert(y_position >= 0);

    //Switch case to define which will be created
    switch(character_code) {
        case INFILTRATOR:
            return new Infiltrator(character_sprites_paths, player_id, x_position, y_position,
                                   character_code);
            break;

        case MAGE:
            return new Mage(character_sprites_paths, player_id, x_position, y_position,
                            character_code);
            break;

        case SOLDIER:
            return new Soldier(character_sprites_paths, player_id, x_position, y_position,
                               character_code);
            break;

        case KNIGHT:
            return new Knight(character_sprites_paths, player_id, x_position, y_position,
                              character_code);
            break;
        //In case of invalid enter, will not happen due to asserts
        default:
            cout << "Invalid value in CharacterFactory\n";
            return nullptr;
            break;
    }
}

/** \fn vector<string> choose_sprite_path(int character_code, unsigned player_id)
  * \protected
  * \brief Method to choose the path to the sprite of the respective player and character.
  * \param character_code int id of the character, a enum is used
  * \param player unsigned id of the player, a enum is used
  * \return a string vector with the paths to the sprites
  */
vector<string>
CharacterFactory::choose_sprite_path(int character_code, unsigned player_id)
{
    //Asserts to validate data
    assert(character_code >= 0);
    assert(character_code < 4);
    assert(player_id < 4);
    assert(player_id >= 0);
    /** \var strings choosen_class
      * Variable to save the choosen character class
      */
    string choosen_class;

    // Switch to set the choosen character class
    switch(character_code) {
        case INFILTRATOR:
            choosen_class = "Infiltrator";
            break;

        case MAGE:
            choosen_class = "Mage";
            break;

        case SOLDIER:
            choosen_class = "Soldier";
            break;

        case KNIGHT:
            choosen_class = "Pesado";
            break;

        //In case of invalid enter, will not happen due to asserts
        default:
            cout << "Invalid value in CharacterFactory\n";
            break;
    }


    /** \var directory string
      * Varaivel para salver nome da cor da equipe de cada um dos players
      */
    string directory;
    // Switch set the dictory to the sprite path
    switch(player_id) {
        case PLAYER_1:
            directory = "Green";
            break;

        case PLAYER_2:
            directory = "Blue";
            break;

        case PLAYER_3:
            directory = "Yellow";
            break;

        case PLAYER_4:
            directory = "Red";
            break;

        default:
            cout << "Invalid value in  CharacterFactory\n";
            break;
    }

    /** \var sprite_vector vector<string>
      * Varaivel para armazenar todos os sprites paths de um personagem que são referentes
      * a cada CharacterState.
      */
    vector<string> sprite_vector;

    //sprite para o estado de IdleState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Idle.png");
    //sprite para o estado de MovingState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Walk.png");
    //sprite para o estado de DeathState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Death.png");
    //sprite para o estado de LightAttackState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Attack.png");
    //sprite para o estado de SpecialState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Special.png");
    //sprite para o estado de HeavyAttackState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Ultimate.png");
    //sprite para o estado de DefenseState
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Defense.png");

    return sprite_vector;
}
