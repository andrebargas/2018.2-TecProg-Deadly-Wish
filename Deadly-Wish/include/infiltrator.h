#ifndef INFILTRATOR_H
#define INFILTRATOR_H

#include "character.h"

using namespace ijengine;

class Infiltrator : public Character {
public:
    Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);
    bool active() const;

protected:
    bool m_active;
    void do_heavy_attack();
    void do_light_attack();
    void do_defense();
    void do_special();
};

#endif
