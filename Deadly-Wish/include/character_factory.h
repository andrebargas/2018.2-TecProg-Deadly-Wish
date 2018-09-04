#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include "character.h"
#include "mage.h"
#include "infiltrator.h"
#include "soldier.h"
#include "knight.h"
#include "util.h"
#include <vector>
#include <string>


using std::vector;
using std::string;
using namespace util;

    class CharacterFactory {
        public:
            CharacterFactory();
            ~CharacterFactory();

    enum {
        KNIGHT,
        SOLDIER,
        MAGE,
        INFILTRATOR
    };

    Character* MakeCharacter(int character_code, unsigned player_id,
     double axis_x_position, double axis_y_position);

protected:
    typedef 
        enum {
            PLAYER_1,
            PLAYER_2,
            PLAYER_3,
            PLAYER_4
        } Players;

    vector<string> ChooseSpritePath(int character_code, unsigned player_id);

protected:
    vector<string> moviment_sprites_paths;
};
#endif