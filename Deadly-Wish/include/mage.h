#ifndef MAGE_H
#define MAGE_H

#include "character.h"

using namespace ijengine;

/*! Permite que o Mago tenha poderes de defesa e ataque,
personagem ativo ou não e suas posições nos eixos x e y
*/
class Mage : public Character {


//! Método Construtor - público
/*!
\param sprite_paths - desenha personagem
\param id - identificador do personagem
\param x - posição no eixo x
\param y - posição no eixo y
\param character_code - codigo do personagem
*/
public:
	Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

//! Métodos Protegidos
protected:

	//! Método void que retorna ataque pesado, poder do ataque: 2000
    void do_heavy_attack();
	//! Método void que retorna ataque leve, poder do ataque: 300
    void do_light_attack();
	//! Método void que retorna a defesa, poder da defesa: 300
    void do_defense();
	// Método void que retorna ataque especial, poder do ataque: 5000
    void do_special();
};

#endif
