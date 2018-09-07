#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

using namespace ijengine;

class Knight : public Character {
public:
    Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

protected:
    void heavy_attack();
    void light_attack();
    void defense();
    void special();
};

#endif