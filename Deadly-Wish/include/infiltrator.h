#ifndef INFILTRATOR_H
#define INFILTRATOR_H

#include "character.h"

using namespace ijengine;

//! Classe para o personagem Infiltrador
/*! Permite que o infiltrador tenha poderes de defesa e ataque,
personagem ativo ou não e suas posições nos eixos x e y
*/
class Infiltrator : public Character {

//! Método Construtor - público
/*!
\param sprite_paths - desenha personagem
\param id - identificador do personagem
\param x - posição no eixo x
\param y - posição no eixo y
\param character_code - codigo do personagem
*/
public:
    Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);
    //! Método que retorna personagem ativo
    bool active() const;

//! Métodos Protegidos
protected:
	//! Método booleano que retorna se o personagem esta ativo
    bool m_active;
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
