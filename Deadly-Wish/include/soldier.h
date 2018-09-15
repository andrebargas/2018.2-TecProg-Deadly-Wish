#ifndef SOLDIER_H
#define SOLDIER_H

#include "character.h"

using namespace ijengine; 

// personagem soldado
class Soldier : public Character {

public:
	
	//param sprite_paths - desenha personagem (eu acho)
	//param id - identificador do personagem
	//param x - posição no eixo x
	//param y - posição no eixo y
	//param character_code - codigo do personagem
    Soldier(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

protected:
	// método de ataque pesado poder do ataque: 2000
    void do_heavy_attack();
    // método de ataque leve, poder do ataque: 300
    void do_light_attack();
    // método para o personagem se defender
    void do_defense();
    // método para o ataque especial, poder do ataque: 5000
    void do_special();
};

#endif
