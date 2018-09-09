#include "character_factory.h"

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

CharacterFactory::CharacterFactory()
{

}

CharacterFactory::~CharacterFactory()
{

}

Character*
CharacterFactory::make_character(int character_code, unsigned player_id, double x_pos, double y_pos)
{
    character_sprites_paths = choose_sprite_path(character_code, player_id);

    switch(character_code) {
        case INFILTRATOR:
            return new Infiltrator(character_sprites_paths, player_id, x_pos, y_pos, character_code);
            break;

        case MAGE:
            return new Mage(character_sprites_paths, player_id, x_pos, y_pos, character_code);
            break;

        case SOLDIER:
            return new Soldier(character_sprites_paths, player_id, x_pos, y_pos, character_code);
            break;

        case KNIGHT:
            return new Knight(character_sprites_paths, player_id, x_pos, y_pos, character_code);
            break;

        default:
            printf("Valor inválido na CharacterFactory\n");
            return nullptr;
            break;
    }
}

vector<string>
CharacterFactory::choose_sprite_path(int character_code, unsigned player_id)
{
    string directory = "Green";
    string choosen_class = "Mage";
    vector<string> sprite_vector;

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

        default:
            printf("Valor inválido na CharacterFactory\n");
            break;
    }

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
            printf("Valor inválido na CharacterFactory\n");
            break;
    }

    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Idle.png");
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Walk.png");
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Death.png");
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Attack.png");
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Special.png");
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Ultimate.png");
    sprite_vector.push_back("Spritesheets/" + directory + "/Spritesheet" + directory + choosen_class + "Defense.png");

    return sprite_vector;
}
