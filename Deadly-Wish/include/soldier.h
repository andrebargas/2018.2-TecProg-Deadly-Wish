/** \file soldier.h
  * \brief Este é o arquivo header da classe Soldier que é filha da classe Character.
  */

#ifndef SOLDIER_H
#define SOLDIER_H

#include "character.h"

using namespace ijengine; 


/** \class Soldier soldier.h "include/soldier.h"
  * \brief Permite que o soldado tenha poderes de defesa e ataque, personagem ativo ou não e suas posições nos eixos x e y.
  */
class Soldier : public Character {

public:

/** \fn Soldier(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
  * \public
  * \brief Método Construtor
  * \param sprite_paths - desenha personagem
  * \param id - identificador do personagem
  * \param x - posição no eixo x
  * \param y - posição no eixo y
  *\param character_code - codigo do personagem
*/
    Soldier(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);


//! Métodos Protegidos
protected:

/** \fn do_heavy_attack()
  * \protected
  * \brief Método poder do ataque: 2000
*/
    void do_heavy_attack();
/** \fn do_defense()
  * \protected
  * \brief Método poder de defesa: 300
*/
    void do_defense();
/** \fn do_light_atack()
  * \protected
  * \brief Método poder do ataque: 300
*/
    void do_light_attack();
/** \fn do_special()
  * \protected
  * \brief Método poder do ataque: 5000
*/
    void do_special();
};

#endif
