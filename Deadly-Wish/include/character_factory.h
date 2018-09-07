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

    Character* make_character(int character_code, unsigned player_id, double x_pos, double y_pos);

protected:
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;

    vector<string> choose_sprite_path(int character_code, unsigned player_id);
    vector<string> character_sprites_paths;
};
#endif
