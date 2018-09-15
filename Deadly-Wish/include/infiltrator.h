#ifndef INFILTRATOR_H
#define INFILTRATOR_H

#include "character.h"

using namespace ijengine;

// personagem infiltrador
class Infiltrator : public Character {

//param sprite_paths - desenha personagem (eu acho)
//param id - identificador do personagem
//param x - posição no eixo x
//param y - posição no eixo y
//param character_code - codigo do personagem
public:
    Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);
    // personagem ativo
    bool active() const;

protected:
	// booleano que define se o personagem esta ativo
    bool m_active;
	// método de ataque pesado, poder do ataque: 2000
    void do_heavy_attack();
	// método de ataque leve, poder do ataque: 300
    void do_light_attack();
	// método de defesa, poder da defesa: 300
    void do_defense();
	// método de ataque especial, poder do ataque: 5000
    void do_special();
};

#endif
