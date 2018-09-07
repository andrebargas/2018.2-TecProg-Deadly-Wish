#ifndef MAGE_H
#define MAGE_H

#include "character.h"

using namespace ijengine;

class Mage : public Character {
public:
	Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

protected:
    void heavy_attack();
    void light_attack();
    void defense();
    void special();
};

#endif
