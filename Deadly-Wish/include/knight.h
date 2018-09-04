#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

using namespace ijengine;

class Knight : public Character {
public:
    Knight(vector<string> sprite_paths, unsigned player_id, double x_position, double y_position, int character_id);

protected:
    void do_heavy_attack();
    void do_light_attack();
    void do_defense();
    void do_special();
};

#endif