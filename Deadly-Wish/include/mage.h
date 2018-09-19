/** \file mage.h
  * \brief Este é o arquivo header da classe Mage que é filha da classe Character.
  */

#ifndef MAGE_H
#define MAGE_H

#include "character.h"

using namespace ijengine;

/** \class Mage mage.h "include/mage.h"
  * \brief Permite que o mago tenha poderes de defesa e ataque, personagem ativo ou não e suas posições nos eixos x e y.
  */
class Mage : public Character {

public:
    /** \fn Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
      * \public
      * \brief Método Construtor
      * \param sprite_paths - desenha personagem
      * \param id - identificador do personagem
      * \param x - posição no eixo x
      * \param y - posição no eixo y
      * \param character_code - codigo do personagem
      */
    Mage(vector<string> sprite_paths, unsigned id, double x, double y, int character_code);

protected:
    /** \fn do_heavy_attack()
      * \protected
      * \brief Método que executa um ataque pesado
      */
    void do_heavy_attack();
 
    /** \fn do_light_attack()
      * \protected
      * \brief Método que executa um ataque leve
      */
    void do_light_attack();
    
    /** \fn do_defense()
      * \protected
      * \brief Método que executa uma defesa
      */
    void do_defense();

    /** \fn do_special()
      * \protected
      * \brief Método que executa um ataque especial
      */
    void do_special();
};

#endif
