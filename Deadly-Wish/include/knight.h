#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

using namespace ijengine;

class Knight : public Character {
public:
    Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

protected:
    void do_heavy_attack();
    void do_defense();
    void do_light_attack();
    void do_special();
};

#endif
