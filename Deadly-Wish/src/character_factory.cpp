#include "character_factory.h"
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

    CharacterFactory::CharacterFactory() {
    }

    CharacterFactory::~CharacterFactory() {
   }

    Character*
    CharacterFactory::MakeCharacter(int character_code, unsigned player_id, double axis_x_position, 
    double axis_y_position) {

        moviment_sprites_paths = ChooseSpritePath(character_code, player_id);
            
            switch(character_code) {
                case INFILTRATOR:
                    return new Infiltrator(moviment_sprites_paths, player_id, 
                    axis_x_position, axis_y_position, character_code);
                break;

                case MAGE:
                    return new Mage(moviment_sprites_paths, player_id,
                    axis_x_position, axis_y_position, character_code);
                break;

                case SOLDIER:
                    return new Soldier(moviment_sprites_paths, player_id,
                    axis_x_position, axis_y_position, character_code);
                break;

                case KNIGHT:
                    return new Knight(moviment_sprites_paths, player_id,
                    axis_x_position, axis_y_position, character_code);
                break;

                default:
                    printf("Valor inválido na CharacterFactory\n");
                    return nullptr;
                break;
                }
    }

    vector<string> CharacterFactory::ChooseSpritePath(int character_code, unsigned player_id) {
    
    
    string choosen_character = "Mage";

    switch(character_code) {
        case INFILTRATOR:
            choosen_character = "Infiltrator";
        break;

        case MAGE:
            choosen_character = "Mage";
        break;

        case SOLDIER:
            choosen_character = "Soldier";
        break;

        case KNIGHT:
            choosen_character = "Pesado";
        break;

        default:
            printf("Valor inválido na CharacterFactory\n");
        break;
    }

    string color_identifier = "Green";

    switch(player_id) {
        case PLAYER_1:
            color_identifier = "Green";
        break;

        case PLAYER_2:
            color_identifier = "Blue";
        break;

        case PLAYER_3:
            color_identifier = "Yellow";
        break;

        case PLAYER_4:
            color_identifier = "Red";
        break;

        default:
            printf("Valor inválido na CharacterFactory\n");
        break;
    }
    
    vector<string>sprite_action_vector;
    sprite_action_vector.push_back("Spritesheets/" + color_identifier + "/Spritesheet" + color_identifier + choosen_character + "Idle.png");
    sprite_action_vector.push_back("Spritesheets/" + color_identifier + "/Spritesheet" + color_identifier + choosen_character + "Walk.png");
    sprite_action_vector.push_back("Spritesheets/" + color_identifier + "/Spritesheet" + color_identifier + choosen_character + "Death.png");
    sprite_action_vector.push_back("Spritesheets/" + color_identifier + "/Spritesheet" + color_identifier + choosen_character + "Attack.png");
    sprite_action_vector.push_back("Spritesheets/" + color_identifier + "/Spritesheet" + color_identifier + choosen_character + "Special.png");
    sprite_action_vector.push_back("Spritesheets/" + color_identifier + "/Spritesheet" + color_identifier + choosen_character + "Ultimate.png");
    sprite_action_vector.push_back("Spritesheets/" + color_identifier + "/Spritesheet" + color_identifier + choosen_character + "Defense.png");
    return sprite_action_vector;
}