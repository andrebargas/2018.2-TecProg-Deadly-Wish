#ifndef MAGE_H
#define MAGE_H

#include "character.h"

using namespace ijengine;

class Mage : public Character {
public:
	Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

protected:
    void do_heavy_attack();
    void do_light_attack();
    void do_defense();
    void do_special();
};

#endif
